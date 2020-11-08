#include<stdio.h>
#include<sys/types.h>
#include<string.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#define SA struct sockaddr
int main()
{
    int sockfd;
    int len;
    struct sockaddr_in servaddr;
    struct sockaddr_in cliaddr;
    sockfd=socket(AF_INET,SOCK_STREAM,0);
    bzero(&servaddr,sizeof(servaddr));
    servaddr.sin_family=AF_INET;
    servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
    servaddr.sin_port=htons(4444);
    inet_pton(AF_INET,"127.0.0.1",&servaddr.sin_addr);
    connect(sockfd,(SA*)&servaddr,sizeof(servaddr));
    char buffer[100];
    printf("Enter file name to be read: ");
    scanf("%s",buffer);
    write(sockfd,buffer,100);
    printf("the file was sent successfully: %s",buffer);
}
