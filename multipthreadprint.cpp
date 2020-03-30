#include<pthread.h>
#include<vector>
#include<unistd.h>
#include<condition_variable>
#include<mutex>
#include<iostream>
#include<thread>
#include<functional>

using namespace std;

int num_=1000;
mutex mutex_;
condition_variable cv_;
vector<thread> threads;
pthread_once_t once_control;

void once_func(){
	unique_lock<mutex> lock(mutex_);
	once_control=PTHREAD_ONCE_INIT;
	cv_.wait(lock);
}

int main(){
	
	for(int i=0;i<3;++i){
		threads.emplace_back
		(
			[i](){
				while(num_>0){
					pthread_once(&once_control,once_func);
					unique_lock<mutex> lock(mutex_);
					if(num_>0){
						cout<<"thread "<<i<<":"<<num_--<<endl;
					}
					else{
					return;
					}
				}
			}
		);
	}
	sleep(4);
	cv_.notify_all();
	for(thread& t:threads){
		t.join();
	}
	return 0;
}

