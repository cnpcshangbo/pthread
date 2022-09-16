#include <pthread.h>
#include <stdlib.h>
#include <iostream>
#define NUM_THREADS 2
using namespace std;
static pthread_mutex_t func_mutex = PTHREAD_MUTEX_INITIALIZER;
int max_num = 100;
bool my_switch = 0;
void func(){
	if (my_switch == 0) {
		pthread_mutex_lock(&func_mutex);
		//Do something that's not thread-safe.
		cout << "something not thread-safe." << endl;
		pthread_mutex_unlock(&func_mutex);
		my_switch = 1;
	}
}

void* worker(void* arg){
	int value = *((int*) arg);
	for (int i = 0; i<=max_num; ){
	// More business logic.
		if (my_switch == 0) {
			pthread_mutex_lock(&func_mutex);
			cout << "worker 0: " << i <<endl;
			i=i+2;
			pthread_mutex_unlock(&func_mutex);
			my_switch = 1;
		}
	}
	return 0;
}
void* worker1(void* arg){
	int value = *((int*) arg);
	for (int i = 1; i<=max_num;){
	// More business logic.
		if (my_switch == 1){
			pthread_mutex_lock(&func_mutex);
			cout << "worker 1: " << i <<endl;
			i=i+2;
			pthread_mutex_unlock(&func_mutex);
			my_switch = 0;
		}
	}
	return 0;
	return 0;
}

int main(int argc, char** argv) {
	pthread_t threads[NUM_THREADS];
	int thread_args[NUM_THREADS];
	int result_code;

	int i = 0;
	//for (unsigned int i = 0; i < NUM_THREADS; ++i) {
	thread_args[i] = i;
	result_code = pthread_create(&threads[i], 0, worker, (void*) &thread_args[i]);
	//}

	i=1;
	thread_args[i] = i;
	result_code = pthread_create(&threads[i], 0, worker1, (void*) &thread_args[i]);

	for (int i=0;i<NUM_THREADS; ++i){
		result_code = pthread_join(threads[i], 0 );
	}
	exit(0);
}
