#include <thread>
#include <mutex>
#include <iostream>
#include <chrono>
#include "iodev.h"
#include "prio.h"

IODEV::IODEV() {
	this->time = 0;
	this->occupied = false;
	this->current = nullptr;
}

void IODEV::consume_time(std::mutex *write) {
	write->lock();
	std::cout << "IODEV procesando task con PID " 
			  << this->current->pid << "." << std::endl;
	write->unlock();
	std::this_thread::sleep_for(std::chrono::milliseconds(this->time));
	current->requirements[0].use_time -= this->time;
	write->lock();
	std::cout << "IODEV finaliza procesamiento de task con PID " 
			  << this->current->pid << "." << std::endl;
	write->unlock();
	this->occupied = false;
}