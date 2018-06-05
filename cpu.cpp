#include <thread>
#include <chrono>
#include "cpu.h"
#include "prio.h"

CPU::CPU() {
	this->time = 0;
	this->occupied = false;
	this->current = nullptr;
}

void CPU::consume_time() {
	this->occupied = true;
	std::this_thread::sleep_for(std::chrono::milliseconds(this->time));
	current->requirements[0].use_time -= this->time;
	this->occupied = false;
}