#include "task.h"
#include "policies.h"
#include "fair_sched_class.h"
#include "cfs_rq.h"
#include "threshold.h"

void task_generator(int max_life_time, float nice_probability, 
					float policy_probability, float window_size,
					FairSchedClass *fair_class, CFSRunQueue *cfs_rq, 
					Threshold *thresh) {
	Task *task_aux;
	int pid = 0;
	int i = 0;
	while(i < 5) {
		task_aux = new Task(pid, max_life_time, nice_probability, 
						policy_probability, window_size);
		if (thresh->under_threshold(task_aux->lifetime)) {
			if (task_aux->policy == SCHED_NORMAL) {
			//task_aux.sched_class = &fair_class;
				task_aux->se.cfs_rq = cfs_rq;
				task_aux->se.my_task = task_aux;
			}
		} 
		else {
			delete task_aux;
		}
		i++;		
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