#include "task.h"
#include "policies.h"

void task_generator(int max_life_time, float nice_probability, 
					float policy_probability, float window_size) {
	Task task_aux;
	int pid = 0;
	while(true) {
		task_aux = Task(pid, max_life_time, nice_probability, 
						policy_probability, window_size);
		// Llamo al threshold. Si paso:
		if (task_aux->policy == SCHED_NORMAL) {
			task_aux->sched_class = &fair_class;
			task_aux->se.cfs_rq = &cfs_rq;
		}
		else 
		
	}

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