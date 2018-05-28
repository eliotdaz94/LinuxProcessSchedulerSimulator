main: main.cpp threshold.cpp
	g++ main.cpp threshold.cpp rb_tree.cpp rb_node.cpp -pthread -std=c++11 -o main.o -I -Wall

run:
	./main.o

rm:
	rm *.o