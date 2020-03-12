#include<sys/types.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<stdio.h>
#include<string.h>
#include<string.h>

#define PORT 8000

int main(){
	int sock,ret;
	char buf[32];
	struct sockaddr_in seraddr;
	sock=socket(AF_INET,SOCK_STREAM,0);
	if(-1==sock){
		perror("socket");
		exit(1);
	}
	seraddr.sin_family=AF_INET;
	seraddr.sin_port=PORT;
	seraddr.sin_addr.s_addr=inet_addr("127.0.0.1");
	ret=connect(sock,(struct sockaddr*)&seraddr,sizeof(seraddr));
	if(-1==ret){
		perror("connect");
		exit(1);
	}
	while(1){
		scanf("%s",buf);
		ret=send(sock,buf,strlen(buf),0);
		if(ret==-1){
			perror("send");
			exit(1);
		}
		memset(buf,0,sizeof(buf));
	}
	return 0;
}
