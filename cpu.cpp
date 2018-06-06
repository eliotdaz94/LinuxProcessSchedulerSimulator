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
	write->lock();
	std::cout << "CPU[" << cpu << "] procesando task con PID " 
			  << this->current->pid << "." << std::endl;
	write->unlock();
	std::this_thread::sleep_for(std::chrono::milliseconds(this->time));
	current->requirements[0].use_time -= this->time;
	write->lock();
	std::cout << "CPU[" << cpu << "] finaliza procesamiento de task con PID " 
			  << this->current->pid << "." << std::endl;
	write->unlock();
	this->occupied = false;
}