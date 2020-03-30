#include<sys/socket.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#include<stdio.h>
#include<arpa/inet.h>

int main(){
	int clisock=socket(AF_INET,SOCK_STREAM,0);
	struct sockaddr_in seraddr;
	seraddr.sin_family=AF_INET;
	seraddr.sin_addr.s_addr=inet_addr("127.0.0.1");
	seraddr.sin_port=8200;
	int ret;
	ret=connect(clisock,(struct sockaddr*)&seraddr,sizeof(seraddr));
	if(ret==-1){
		perror("connect");
		exit(1);
	}
	char sendbuf[1024];
	size_t msgsize;
	while(1){
		memset(sendbuf,0,1024);
		scanf("%s",sendbuf);
		msgsize=write(clisock,sendbuf,sizeof(sendbuf));
		if(msgsize<0){
			perror("write");
			exit(1);
		}
		if(msgsize==0){
			break;
		}
	}
	return 0;
}
