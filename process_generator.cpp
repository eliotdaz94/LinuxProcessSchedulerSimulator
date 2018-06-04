#include <chrono>
#include <cmath>
#include <iostream>
#include <mutex>
#include <random>
#include <stdexcept>
#include <string>
#include <thread>
#include <vector>
#include <stdlib.h>
#include <unistd.h>

#define PI 3.14159265

using namespace std;

class Threshold {
	
	public:
		
		double boundary;
		double amplitude;
		double initial_phase;
		double offset;
		double granularity;
		mutex sync_threshold;

		Threshold(double boundary, double amplitude, double initial_phase, double offset, double granularity) {
			this->boundary = boundary;
			this->amplitude = amplitude;
			this->initial_phase = initial_phase;
			this->offset = offset;
			this->granularity = granularity;
		}

		double get_boundary() {
			return this->boundary;
		}

		void set_threshold(double frequency) {
			this->boundary = this->amplitude * cos(frequency * 180 / PI + this->initial_phase) + this->offset;
		}

		bool under_threshold(double value) {
			bool is_under_threshold;
			this->sync_threshold.lock();
			(value <= this->boundary) ? is_under_threshold = true : is_under_threshold = false;
			this->sync_threshold.unlock();
			return is_under_threshold;
		}

		void move_threshold() {
			double ticks = 360/this->granularity;
			while (true) {
				for (int i = 0; i < ceil(ticks); i++) {
					this->sync_threshold.lock();
					set_threshold(double(i) * this->granularity);
					this->sync_threshold.unlock();
				}
			}
		}
};

int main(){
	//Process p(1,1000,0.8,0.8,0.3);
	//Threshold t(0,10,15);
	return 0;
}
/*
int main() {

	double lifetime;
	double boundary;
	bool is_created;

	Threshold threshold(5, 5, 0, 5, 1e-9);
	thread move(&Threshold::move_threshold, &threshold);

	default_random_engine generator;
	uniform_real_distribution<double> distribution(0, 10);

	while (true) {
		lifetime = distribution(generator);
		is_created = threshold.under_threshold(lifetime);
		boundary = threshold.get_boundary();
		cout << "Threshold: " << boundary << "\t| Lifetime: " << lifetime << "\t| Created?: " << is_created << endl;
		usleep(0.20 * 1000000);
	}

	return 0
}
*/