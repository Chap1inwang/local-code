#pramga once
#include<stdint.h>

namespace CurrentThread{
	extern __thread int t_cachedTid;
	extern __thread char t_tidString[32];
	extern __thread int t_tidStringLength;
	extern __thread const char* t_threadName;
	void cacheTid();
	inline int Tid(){
		if(__builtin_except(!!t_cachedTid,0)){    //这个函数的作用是允许程序员将最可能执行的代码分支告诉编译器，方便编译器对代码进行优化
			cacheTid();
		}                                         //两次取反保证将t_cachedTid转化成bool，
		return t_cachedTid;
	}
	
	inline const char* tidString(){
		return t_tidString;
	}

	inline int tidStringLength(){
		return t_tidStringLength;
	}

	inline const char* name(){
		return t_threadName;
	}
}
