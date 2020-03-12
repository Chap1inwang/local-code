#ifndef _THREADPOOL_H_
#define _THREADPOOL_H_

#include<thread>
#include<mutex>
#include<condition_variable>
#include<future>
#include<functional>
#include<stdexcept>
#include<vector>
#include<queue>

using namespace std;

class ThreadPool {
public:
	ThreadPool(size_t);
	template<class F,class... Args>
	auto enqueue(F&& f,Args&&... args)->future<typename result_of<F(Args...)>::type>;
	~ThreadPool();
private:
	vector<thread> workers;
	queue<function<void()> > tasks;

	mutex queue_mutex;
	condition_variable condition;
	bool stop;
};

inline ThreadPool::ThreadPool(size_t threads):stop(false){
	for(size_t i=0;i<threads;++i){    //创建指定的线程数
		//通过在vector中添加thread对象时使用thread的构造函数创建线程？
		workers.emplace_back(
			[this]{   //this？
				for(;;){  //当第一次创建了线程后，完成了之后task属于临时对象，被销毁，但此处的for(;;)循环
					      //不会再次创建线程，只会通过更换可调用对象(即新的task对象)实现新的线程
					function<void()> task;
					{
						unique_lock<mutex> lock(queue_mutex);
						this->condition.wait(lock,[this]{return this->stop||!this->tasks.empty(); });
						if(this->stop&&this->tasks.empty()){
							return;
						}
						task=move(this->tasks.front()); //move函数无条件将参数转化为右值，减少资源的浪费，
						this->tasks.pop();
					}
					task();
				}
			}
		);
	}
}

template<class F,class... Args>
auto ThreadPool::enqueue(F&& f,Args&&... args)->future<typename result_of<F(Args...)>::type>  //lambda表达式，返回类型为F(Args)函数对象的返回类型
{                                                                                             //typename只是强调后面声明的是一个类型
	using return_type=typename result_of<F(Args...)>::type;

	auto task=make_shared<packaged_task<return_type()> >(bind(forward<F>(f),forward<Args>(args)...)); //声明一个packaged_task
	future<return_type> res=task->get_future();
	{
		unique_lock<mutex>lock(queue_mutex);
		if(stop){
			throw runtime_error("enqueue on stopped ThreadPool");
		}
		tasks.emplace([task](){ (*task)(); });
	}
	condition.notify_one();
	return res;
}


inline ThreadPool::~ThreadPool(){
	{
		unique_lock<mutex> lock(queue_mutex);
		stop=true;
	}
	condition.notify_all();
	for(thread &worker:workers){
		worker.join();
	}
}

#endif


