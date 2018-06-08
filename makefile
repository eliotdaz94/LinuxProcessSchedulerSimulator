main: main.cpp
	g++ main.cpp task.cpp task_generator.cpp threshold.cpp rb_tree.cpp \
		rb_node.cpp sched_entity.cpp fair_sched_class.cpp load_weight.cpp \
		cfs_rq.cpp cpu.cpp dispatcher.cpp io_dev.cpp io_dispatcher.cpp \
		-pthread -std=c++11 -o main.o -I -Wall

run:
	./main.o 4 1000

rm:
	rm *.o
	rm salida.txt