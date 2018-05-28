#ifndef THRESHOLD_H
#define THRESHOLD_H

#include <mutex>

class Threshold {
	
	public:
		
		double boundary;
		double amplitude;
		double initial_phase;
		double offset;
		double granularity;
		std::mutex sync_threshold;

		Threshold(double boundary, double amplitude, double initial_phase, double offset, double granularity);

		double get_boundary();

		void set_threshold(double frequency);

		bool under_threshold(double value);

		void move_threshold();
};

#endif