#include <thread>
#include <mutex>
#include <iostream>
#include <chrono>
#include "cpu.h"
#include "prio.h"

CPU::CPU() {
	this->time = 0;
	this->occupied = false;
	this->current = nullptr;
}

void CPU::consume_time(int cpu, std::mutex *write) {
	//this->use.lock();
	write->lock();
		std::cout << "CPU[" << cpu << "] procesando task con PID " 
			 	  << this->current->pid << "." << std::endl;
	write->unlock();
	std::this_thread::sleep_for(std::chrono::milliseconds(this->time));
	if (current->requirements[0].use_time != this->time) {
		//write->lock();
		//std::cout << " PID " << this->current->pid <<" me sobra tiempo: " << current->requirements[0].use_time << std::endl;
		//std::cout << "Y consumi: " << this->time << std::endl;
		//write->unlock();
		current->requirements[0].use_time -= this->time;
	}
	else {
		current->requirements.erase(current->requirements.begin());
	}
	write->lock();
	std::cout << "CPU[" << cpu << "] finaliza procesamiento de task con PID " 
			  << this->current->pid << "." << std::endl;
	write->unlock();
	this->occupied = false;
	//this->use.unlock();
}