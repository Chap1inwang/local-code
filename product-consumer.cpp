#include<queue>
#include<iostream>
#include<thread>
#include<cstdlib>
#include<ctime>
#include<mutex>
#include<condition_variable>
#include<unistd.h>

using namespace std;
queue<int> buffer;
mutex mutex_;
condition_variable cv;
bool quit=false;

int main(){
	srand((int)time(0));
	vector<thread> productor_threads;
	for(int i=0;i<5;++i){
		productor_threads.emplace_back(
			[i](){
				while(quit==false){
					unique_lock<mutex> lock(mutex_);
					if(buffer.size()<300){
						int num=rand()%100;
						buffer.push(num);
						cout<<"productor_threads "<<i<<": "<<num<<endl;
					}
					else{
						cout<<"buffer full"<<endl;
						cv.notify_all();
						cv.wait(lock);
					}
				}
			}
		);
	}
	vector<thread> consumer_threads;
	for(int i=0;i<3;++i){
		consumer_threads.emplace_back(
			[i](){
				while(quit==false){
					unique_lock<mutex> lock(mutex_);
					if(buffer.size()>0){
						cout<<"consumer_threads "<<i<<": "<<buffer.front()<<endl;
						buffer.pop();
					}
					else{
						cout<<"buffer empty"<<endl;
						cv.notify_all();
						cv.wait(lock);
					}
				}
			}
		);
	}
	sleep(1);
	quit=true;
	cv.notify_all();
	for(auto& t:productor_threads){
		t.join();
	}
	for(auto& t:consumer_threads){
		t.join();
	}
	return 0;
}
