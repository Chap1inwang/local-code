#include<pthread.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<unistd.h>
#include<string.h>
#include<stdio.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<arpa/inet.h>

extern void* thread_handle(void* arg){
	int msgsize=0;
	char recvbuf[1024]={0};
	int clisock=*((int*)arg);
	int tid=pthread_self();
	while(1){
		msgsize=read(clisock,recvbuf,sizeof(recvbuf));
		if(msgsize>0){
			printf("msg from %d:%s\n",tid,recvbuf);
		}
		else if(msgsize==0){
			printf("client%d close\n",tid);
			break;
		}
		else{
			perror("read");
		}
	}
	close(clisock);
	return 0;
}

int main(){
	int sersock,clisock;
	struct sockaddr_in seraddr, cliaddr;
	sersock=socket(AF_INET,SOCK_STREAM,0);
	seraddr.sin_family=AF_INET;
	seraddr.sin_port=8100;
	seraddr.sin_addr.s_addr=inet_addr("127.0.0.1");
	int ret;
	ret=bind(sersock,(struct sockaddr*)&seraddr,sizeof(seraddr));
	if(ret==-1){
		perror("bind");
		exit(1);
	}
	ret=listen(sersock,5);
	while(1){
		socklen_t socksize=sizeof(cliaddr);
		clisock=accept(sersock,(struct sockaddr*)&cliaddr,&socksize);
		if(clisock==-1){
			perror("accept");
			continue;
		}
		pthread_t tid;
		pthread_create(&tid,NULL,thread_handle,(void*)&clisock);
		pthread_detach(tid);
	}
	close(clisock);
	return 0;
}
