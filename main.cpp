#include "task.h"
#include "threshold.h"
//#include "sched_class.h"
#include "cfs_rq.h"
#include "fair_sched_class.h"

int main() {
	FairSchedClass fair_class;
	CFSRunQueue cfs_rq;
	Task t1(1,1000,0.8,0.8,0.3);
	//Threshold t(0.0,10.0,15.0,2.0,5.0);
	return 1;
}