#ifndef IO_DISPATCH
#define IO_DISPATCH

void io_dispatch(IODev *io_device, int *nr_task_gen, CFSRunQueue *cfs_rq,
				 std::mutex *write, bool *exit);

#endif