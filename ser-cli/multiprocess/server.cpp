#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<signal.h>

void signal_handle(int sig){
	printf("recvive %d,calling wait...\n",sig);
	wait(NULL);
	printf("wait done\n");
}

int main(){
	int sersock,clisock;
	struct sockaddr_in seraddr,cliaddr;
	sersock=socket(AF_INET,SOCK_STREAM,0);
	seraddr.sin_family=AF_INET;
	seraddr.sin_port=8000;
	seraddr.sin_addr.s_addr=inet_addr("127.0.0.1");
	int ret;
	int on=1;
	ret=setsockopt(sersock,SOL_SOCKET,SO_REUSEADDR,(void*)&on,(socklen_t)sizeof(on));
	if(ret==-1){
		perror("setsockopt");
		exit(1);
	}
	ret=bind(sersock,(struct sockaddr*)&seraddr,(socklen_t)sizeof(seraddr));
	if(ret==-1){
		perror("bind");
		exit(1);
	}
	ret=listen(sersock,5);
	if(ret==-1){
		perror("listen");
		exit(1);
	}
	signal(SIGCHLD,signal_handle);
	while(1){
		socklen_t size=sizeof(cliaddr);
		clisock=accept(sersock,(struct sockaddr*)&cliaddr,&size);
		int pid=fork();
		if(pid==0){
			close(sersock);
			int count;
			char recvbuf[1024]={0};
			while(1){
				count=read(clisock,recvbuf,sizeof(recvbuf));
				if(count==-1){
					perror("read");
					exit(1);
				}
				if(count>0){
					printf("from proccess %d:%s\n",getpid(),recvbuf);
				}
				if(count==0){
					break;
				}
				memset(recvbuf,0,sizeof(recvbuf));
			}
			return 0;
		}
		else{
			close(clisock);
		}
	}
	return 0;
}
