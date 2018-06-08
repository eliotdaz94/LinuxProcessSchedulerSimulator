#include <thread>
#include <mutex>
#include <iostream>
#include <chrono>
#include "io_dev.h"
#include "prio.h"

IODev::IODev() {
	this->time = 0;
	this->occupied = false;
	this->current = nullptr;
}

void IODev::consume_time(std::mutex *write) {
	this->use.lock();
	write->lock();
	std::cout << "IODev procesando task con PID " 
			  << this->current->pid << "." << std::endl;
	write->unlock();
	std::this_thread::sleep_for(std::chrono::milliseconds(this->time));
	write->lock();
	std::cout << "IODev finaliza procesamiento de task con PID " 
			  << this->current->pid << "." << std::endl;
	write->unlock();
	this->current->requirements.erase(this->current->requirements.begin());
	this->occupied = false;
	this->use.unlock();
}