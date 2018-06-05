#include <thread>
#include <chrono>
#include "cpu.h"
#include "prio.h"

CPU::CPU() {
	this->occupied = false;
	this->current = nullptr;
}

void CPU::consume_time(unsigned int time) {
	std::this_thread::sleep_for(std::chrono::milliseconds(time));
	current->requirements[0].use_time -= time;
	if (current->requirements[0].use_time == 0) {
		current->requirements.erase(current->requirements.begin());
		// No estoy seguro de esto.
		current->se.vruntime = 0;
	}
	else {
		if (current->se.load.weight == NICE_0_LOAD) {
			current->se.vruntime += time;	
		}
		else {
			current->se.vruntime += time * NICE_0_LOAD / current->se.load.weight;
		}
	}
}