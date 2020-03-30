#include<sys/socket.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<iostream>
#include<pthread.h>
#include<arpa/inet.h> //sockaddr_in需要的头文件
#include<string.h>

#define PORT 8000

void* clihandler(void* arg){
	pthread_detach(pthread_self());
	int ret;
	int fd=*(int*)arg;
	char buf[32]={0};
	while(1){
		sleep(1);
		ret=recv(fd,buf,sizeof(buf),0);
		if(-1==ret){
			perror("revc");
			exit(1);
		}
		printf("recv from %d client %s!\n",fd,buf);
		memset(buf,0,sizeof(buf));
	}
}

int main(){
	struct sockaddr_in seraddr,cliaddr;
	int sock=socket(AF_INET,SOCK_STREAM,0);
	struct sockaddr_in;
	if(sock==-1){
		perror("socket");
		exit(1);
	}
	seraddr.sin_family=AF_INET;
	seraddr.sin_port=PORT;
	seraddr.sin_addr.s_addr=inet_addr("127.0.0.1");
	int on=1;
	if(setsockopt(sock,SOL_SOCKET,SO_REUSEADDR,&on,sizeof(int))<0){
		perror("setsockopt");
		exit(1);
	}
	int ret=bind(sock,(struct sockaddr*)&seraddr,sizeof(seraddr));
	if(-1==ret){
		perror("bind");
		exit(1);
	}
	ret=listen(sock,5);
	if(ret==-1){
		perror("listen");
		exit(1);
	}
	while(1){
		int length=sizeof(cliaddr);
		memset(&cliaddr,0,sizeof(cliaddr));
		int fd;
		fd=accept(sock,(struct sockaddr*)&cliaddr,(socklen_t*)&length);
		if(fd==-1){
			perror("accept");
			exit(1);
		}
		printf("accept port %d fd %d\n",cliaddr.sin_port,fd);
		pthread_t tid;
		ret=pthread_create(&tid,NULL,clihandler,&fd);
		if(ret==-1){
			perror("pthread_create");
		}
	}
	return 0;
}
