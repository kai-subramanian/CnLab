#include<stdio.h>
#include<sys/types.h>
#include<string.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#define SA struct sockaddr
#define LISTENQ 5
int main(){
    int fd,sockfd,listenfd,connfd;
    socklen_t client;
    struct sockaddr_in servaddr;
    struct sockaddr_in cliaddr;
    char buffer[100];
    pid_t childpid;
    listenfd=socket(AF_INET,SOCK_STREAM,0);
    bzero(&servaddr,sizeof(servaddr));

    servaddr.sin_family=AF_INET;
    servaddr.sin_addr.s_addr=htonl("127.0.0.1");
    servaddr.sin_port=htons(4444);

    bind(listenfd,(SA*)&servaddr,sizeof(servaddr));

    listen(listenfd,LISTENQ);

    client=sizeof(cliaddr);
    connfd=accept(listenfd,(SA*)&cliaddr,&client);
    read(connfd,buffer,100);

    FILE *fp;
    fp=fopen(buffer,"r");
    fscanf(fp,"%s",buffer);
    //fprintf(fp,"%s",buffer);
    printf("The data is: %s",buffer);
}
