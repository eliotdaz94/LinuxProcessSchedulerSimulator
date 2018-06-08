#include <vector>
#include <thread>
#include <mutex>
#include <iostream>
#include "task.h"
#include "io_dev.h"
#include "cfs_rq.h"
#include "fair_sched_class.h"

void io_dispatch(IODev *io_device, CFSRunQueue *cfs_rq, std::mutex *write,
				 bool *exit) {
	Task *prev_task;
	Task *next_task;

	//while (!*exit){
	while(!*exit) {
		if (!io_device->occupied) {
			if (io_device->current != nullptr) {
				prev_task = io_device->current;
				// Si ya no quedan rafagas, entonces el task ha finalizado su 
				// ejecucion y se elimina. task.state = 1.
				if (prev_task->requirements.empty()) {
					prev_task->state = 1;
					write->lock();
					std::cout << "Task con PID " << prev_task->pid 
						  	  << " ha finalizado su ejecucion." << std::endl;
					write->unlock();
					delete prev_task;	
				}
				// La rafaga actual es de tipo CPU, entonces el task 
				// esta listo para ser ejecutado y se encola de nuevo en el
				//arbol del CFS. task.state = 0.
				else {
					prev_task->state = 0;
					write->lock();
					cfs_rq->dispatcher.lock();
					prev_task->sched_class->enqueue_task(prev_task,0,0);
					cfs_rq->dispatcher.unlock();
					std::cout << "Task con PID " << prev_task->pid 
							  << " encolandose en arbol del CFS." << std::endl;
					write->unlock();
				}
				io_device->current = nullptr;
			}
			if (!io_device->wait_queue.empty()) {
				io_device->use.lock();
				next_task = io_device->wait_queue.front();
				io_device->wait_queue.erase(io_device->wait_queue.begin());
				io_device->use.unlock();
				io_device->occupied = true;
				io_device->time = next_task->requirements.front().use_time;
				io_device->current = next_task;
				std::thread io_processing(&IODev::consume_time, io_device, write);
				io_processing.detach();
			}
		}
	}
	write->lock();
	std::cout << "IO Dispatch terminando ejecucion." << std::endl;
	write->unlock();
}