#pramga once
#include<pthread.h>
#include<functional>
#include<string>
#include<memory>
#include<unistd.h>
#include<sys/syscall.h>
#include"CountDownLatch.h"
#include"noncopyable.h"

class Thread{
	typedef std::function<void()> ThreadFunc;
private:
	bool started_;
	bool joined_;
	pthread_t pthreadId_;
	pid_t tid_;
	ThreadFunc func_;
	string name_;
	CountDownLatch latch_;
	void setDefaultName();
public:
	explicit Thread(const ThreadFunc&, const string& name=string());
	~Thread();
	void start();
	int join();
	bool started_() const {return started_};
	pid_t tid() const {return tid_;}
	const string& name(){
		return name_;
	}
};


