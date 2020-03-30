#include<iostream>
#include<thread>
#include<sys/socket.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>

using namespace std;

void thread_handle(int clisock,int sersock){
	//close(sersock);
	char recvbuf[1024];
	int msgsize;
	while(1){
		msgsize=read(clisock,recvbuf,1024);
		if(msgsize==-1){
			perror("read");
			exit(1);
		}
		else if(msgsize>0){
			cout<<"msg from "<<this_thread::get_id()<<": ";
			printf("%s\n",recvbuf);
		}
		else if(msgsize==0) { 
			cout<<"msg from "<<this_thread::get_id()<<": ";
			printf("close\n");
			break;
		}
		memset(recvbuf,0,1024);
	}
}

int main(){
	int sersock,clisock;
	struct sockaddr_in seraddr,cliaddr;
	seraddr.sin_family=AF_INET;
	seraddr.sin_addr.s_addr=inet_addr("127.0.0.1");
	seraddr.sin_port=8200;
	sersock=socket(AF_INET,SOCK_STREAM,0);
	int ret;
	ret=bind(sersock,(struct sockaddr*)&seraddr,sizeof(seraddr));
	if(ret==-1){
		perror("bind");
		exit(1);
	}
	ret=listen(sersock,5);
	if(ret==-1){
		perror("listen");
		exit(1);
	}
	while(1){
		memset((void*)&cliaddr,0,sizeof(cliaddr));
		socklen_t clisize=sizeof(cliaddr);
		clisock=accept(sersock,(struct sockaddr*)&cliaddr,&clisize);
		thread threadobj(thread_handle,clisock,sersock);
		threadobj.detach();
	}
	return 0;
}
