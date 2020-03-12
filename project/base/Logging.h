#pragme once

#include<pthread.h>
#include<stdio.h>
#include<string.h>
#include<string>
#include"LogStream.h"

class AsyncLogging;

class Logger{
private:
	class Impl{
	public:
		Impl(const char* failname,int line);
		void formaTime();

		LogStream stream_;
		int line_;
		std::string basename_;
	};
	Impl impl_;
	static std::string logFileName_;

public:
	Logger(const char* fileName,int line);
	~Logger();
	LogStream& stream(){
		return impl_.stream_;
	}

	static void setLogFileName(std::string fileName){
		logFileName_=fileName;
	}
	static std::string getLogFileName(){
		return logFileName_;
	}

};

#define LOG Logger(__FILE__,__LINE__).stream() //c++预定义的几个宏，__FILE__：在源代码中插入当前源代码行号
                                              //                    __LINE__：在源代码中插入当前源文件名
