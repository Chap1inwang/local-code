#pramga once
#include"Condition.h"
#include"MutexLock.h"
#include"noncopyable.h"

class CountDownLatch:noncopyable{
private:
	MutexLock mutex_;
	Condition Condition_;
	int count_;
public:
	explicit CountDownLatch(int count);
	void wait();
	void countDown();
};

CountDownLatch::CountDownLatch(int count):mutex_(),Condition_(mutex_),count_(count){}

void CountDownLatch::wait(){
	MutexLockGuard lock(mutex_);
	while(count_>0){
		Condition_.wait();
	}
}

void CountDownLatch::countDown(){
	MutexLockGuard lock(mutex_);
	--count;
	if(count_==0){
		Condition_.notifyAll();
	}
}
