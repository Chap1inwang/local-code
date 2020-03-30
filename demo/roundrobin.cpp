#include<thread>
#include<iostream>
#include<condition_variable>
#include<functional>
#include<mutex>
#include<vector>

using namespace std;

mutex mutex_;
int count=400;
condition_variable wake_t2,wake_t3,wake_t4,wake_t1;

void thread1func(int i){
	while(count>0){
		unique_lock<mutex> lock(mutex_);
		wake_t1.wait(lock);
		if(count>0){
			cout<<"thread "<<i<<": "<<count--<<endl;
		}
		else{
			wake_t2.notify_one();
			cout<<"thread "<<i<<" exit"<<endl;
			return;
		}
		wake_t2.notify_one();
	}
}

void thread2func(int i){
	while(count>0){
		unique_lock<mutex> lock(mutex_);
		wake_t2.wait(lock);
		if(count>0){
			cout<<"thread "<<i<<": "<<count--<<endl;
		}
		else{
			wake_t3.notify_one();
			cout<<"thread "<<i<<" exit"<<endl;
			return;
		}
		wake_t3.notify_one();
	}
}
void thread3func(int i){
	while(count>0){
		unique_lock<mutex> lock(mutex_);
		wake_t3.wait(lock);
		if(count>0){
			cout<<"thread "<<i<<": "<<count--<<endl;
		}
		else{
			wake_t4.notify_one();
			cout<<"thread "<<i<<" exit"<<endl;
			return;
		}
		wake_t4.notify_one();
	}
}
void thread4func(int i){
	while(count>0){
		unique_lock<mutex> lock(mutex_);
		wake_t4.wait(lock);
		if(count>0){
			cout<<"thread "<<i<<": "<<count--<<endl;
		}
		else{
			wake_t1.notify_one();
			cout<<"thread "<<i<<" exit"<<endl;
			return;
		}
		wake_t1.notify_one();
	}
	cout<<"thread "<<i<<" exit"<<endl;
}

int main(){
	vector<thread> threads;
	threads.emplace_back(bind(thread1func,1));
	threads.emplace_back(bind(thread2func,2));
	threads.emplace_back(bind(thread3func,3));
	threads.emplace_back(bind(thread4func,4));
	wake_t1.notify_one();
	for(thread& t:threads){
		t.join();
	}
	return 0;
}
