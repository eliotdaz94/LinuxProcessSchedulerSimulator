main: main.cpp threshold.cpp
	g++ main.cpp task.cpp task_generator.cpp threshold.cpp rb_tree.cpp rb_node.cpp sched_entity.cpp fair_sched_class.cpp load_weight.cpp cfs_rq.cpp -pthread -std=c++11 -o main.o -I -Wall

run:
	./main.o

rm:
	rm *.o