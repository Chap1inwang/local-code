#pragma once 
#include<memory>
#include<string>
#include"FileUtil.h"
#include"MutexLock.h"
#include"noncopyable.h"

//提供自动归档的功能
class LogFile:noncopyable{
private:
	int count_;
	std::unique_ptr<MutexLock> mutex_;
	std::unique_ptr<AppendFile> file_;
	const std::string basename_;
	const int flushEveryN_;
	
	void append_unlocked(const char* logline,int len);

public:
	LogFile(std::string& basename,int flushEveryN=1024);
	~LogFile();

	void append(const* char* logline,int len);
	void flush();
	bool rollFile();
};
