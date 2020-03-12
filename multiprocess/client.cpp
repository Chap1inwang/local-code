#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<string.h>
#include<stdio.h>
#include<arpa/inet.h>
int main(){
	int clisock=socket(AF_INET,SOCK_STREAM,0);
	struct sockaddr_in seraddr;
	seraddr.sin_family=AF_INET;
	seraddr.sin_port=8000;
	seraddr.sin_addr.s_addr=inet_addr("127.0.0.1");
	int ret;
	ret=connect(clisock,(struct sockaddr*)&seraddr,(socklen_t)sizeof(seraddr));
	if(ret==-1){
		perror("connect");
		exit(1);
	}
	char sendbuf[1024]={0};
	int count;
	while(1){
		scanf("%s",sendbuf);
		count=write(clisock,sendbuf,sizeof(sendbuf));
		if(count==-1){
			perror("write");
			exit(1);
		}
		memset(sendbuf,0,sizeof(sendbuf));
	}
	return 0;
}
