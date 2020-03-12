#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/wait.h>
#include<signal.h>
#include<sys/stat.h>

#define MAXFILE 65535

volatile sig_atomic_t  _running=1;

void sigterm_handler(int arg){
	_running==0;
}

int main(){
	pid_t pc;
	int i, fd,len;
	char* buf="this is a dameon\n";
	len=strlen(buf);
	pc=fork();
	if(pc<0){
		printf("error fork\n");
		exit(1);
	}
	else if(pc>0){
		exit(0);
	}
	//第二步：在子进程中创建新的对话
	setsid();
	//第三步：改变当前的目录为根目录
	chdir("/");
	//第四步：重设文件权限掩码
	umask(0);
	//第五步：关闭文件描述符
	for(i=0;i<MAXFILE;++i){
		close(i);
	}
	signal(SIGTERM,sigterm_handler);
	while(_running){
		if((fd=open("/tmp/dameon.log",O_CREAT|O_WRONLY|O_APPEND,0666))<0){
			printf("open error\n");
			exit(1);
		}
		write(fd,buf,len+1);
		close(fd);
		usleep(10*1000);
	}

	//第六步：守护进程退出处理
	return 0;
}
