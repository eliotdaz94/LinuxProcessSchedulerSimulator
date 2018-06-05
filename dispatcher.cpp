#include <iostream>
#include "dispatcher.h"
#include "cpu.h"
#include "cfs_rq.h"

void dispatcher(CPU cpus[], int nr_cpus, CFSRunQueue *cfs_rq) {
	for (int i = 0; i < nr_cpus; i++) {
		if (!cpus[i].occupied) {
			std::cout << "CPU[" << i << "] esta ocioso." << std::endl;
			if (!cpus[i].current) {
				// Calcula lo que tiene que calcular.
				// Lo encola dependiendo del estado.
			}
			// Selecciona al siguiente task.
			// Le asigna por afinidad el CPU.
		}
	}
}