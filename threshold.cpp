#include <cmath>
#include <thread>
#include "threshold.h"
#include <iostream>

#define PI 3.14159265

Threshold::Threshold(double boundary, double amplitude, double initial_phase, double offset, double granularity) {
	this->boundary = boundary;
	this->amplitude = amplitude;
	this->initial_phase = initial_phase;
	this->offset = offset;
	this->granularity = granularity;
	this->exit = false;
}

double Threshold::get_boundary() {
	return this->boundary;
}

void Threshold::set_threshold(double frequency) {
	this->boundary = this->amplitude * cos(frequency * 180 / PI + this->initial_phase) + this->offset;
}

bool Threshold::under_threshold(double value) {
	bool is_under_threshold;
	this->sync_threshold.lock();
	(value <= this->boundary) ? is_under_threshold = true : is_under_threshold = false;
	this->sync_threshold.unlock();
	return is_under_threshold;
}

void Threshold::move_threshold() {
	double ticks = 360/this->granularity;	
	//std::cout << ticks << std::endl;	
	while (!this->exit) {
		std::cout << this->exit << std::endl;
		for (int i = 0; i < ceil(ticks); i++) {
			this->sync_threshold.lock();
			set_threshold(double(i) * this->granularity);
			//std::cout << this->boundary << std::endl;
			this->sync_threshold.unlock();
			if (this->exit) {
				break;
			}
		}
		
	}
}