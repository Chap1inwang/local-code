#include<thread>
#include<unistd.h>
#include<iostream>
#include<mutex>
#include<condition_variable>
#include<functional>

using namespace std;

mutex mymutex;
condition_variable cv;

void thread_1(){
	unique_lock<mutex> lck(mymutex);
	cv.wait(lck);
	cout<<"thread_1..."<<endl;
}

void thread_2(){
	unique_lock<mutex>  lck(mymutex);
	cv.wait(lck);
	cout<<"thread_2..."<<endl;
}

int main(){
	thread t1(thread_1);
	thread t2(thread_2);
	sleep(1);
	cv.notify_all();
	t1.join();
	t2.join();
	return 0;
}
