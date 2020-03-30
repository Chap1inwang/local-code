#include<stdio.h>
#include<unistd.h>
#include<sys/epoll.h>

int main(){
	int epfd,nfds;
	struct epoll_event care_event,recv_event[5];
	epfd=epoll_create(1);
	care_event.data.fd=STDIN_FILENO;
	care_event.events=EPOLLIN;
	epoll_ctl(epfd,EPOLL_CTL_ADD,STDIN_FILENO,&care_event);
	for(;;){
		nfds=epoll_wait(epfd,recv_event,5,-1);
		for(int i=0;i<nfds;++i){
			if(recv_event[i].data.fd==STDIN_FILENO){
				printf("welcome to epoll world!\n");
			}
		}
	}
	return 0;
}
