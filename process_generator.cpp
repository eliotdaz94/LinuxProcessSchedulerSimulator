#include <vector>
#include <string>
#include <random>
#include <iostream>
#include <chrono>

using namespace std;

class Resource {
	public:
		string type;
		int use_time;
		
		Resource() {};
		
		Resource(string t, int u_t) {type = t; use_time = u_t;}
};

class Process {
	public:
		string type;
		int PID;
		int nice;
		int life_time;
		int v_runtime;
		vector<Resource> requirements;

		Process() {};
		
		Process(int pid, int max_life_time, float nice_probability, float type_probability){
			unsigned seed = chrono::system_clock::now().time_since_epoch().count();
			default_random_engine generator(seed);
			uniform_int_distribution<int> dist(1,10);		
			int aux;
			int u_t;

			// En caso de que consideremos el Real-Time Scheduler. El proceso puede ser de 
			// tipo CFS con una probabilidad nice_probability o Real-Time con una probabilidad
			// 1-nice_probability.
			aux = dist(generator);
			cout << "Aux type: " << aux << endl;
			if (aux > type_probability * 10) {
				type = "Real-Time";
			}
			else {
				type = "CFS";
			}

			PID = pid;
			
			// El proceso puede tener un valor nice por defecto (0) con probabilidad 
			// nice_probability o puede tener un valor distinto con probabilidad 
			// 1-nice_probability.
			aux = dist(generator);
			cout << "Aux nice: " << aux << endl;
			if (aux > nice_probability * 10) {
				dist = uniform_int_distribution<int>(-19,20);
				nice = dist(generator);
			}
			else {
				nice = 0;
			}

			dist = uniform_int_distribution<int>(1,max_life_time);
			life_time = dist(generator);
			aux = 0;
			while (aux < life_time) {
				dist = uniform_int_distribution<int>(aux+1,life_time);
				u_t = dist(generator);
				aux += u_t;
				requirements.push_back(Resource(u_t,));
				cout << " " << u_t << " ";
			}
			cout << endl;
			v_runtime = 0;
			
			cout << "PID: " << PID << endl;
			cout << "Nice value: " << nice << endl;
			cout << "Life time value: " << life_time << endl;
		}
};

int main(){
	Process p(1,150,0.8,0.8);
	return 0;
}