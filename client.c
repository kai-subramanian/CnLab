#include <netdb.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h> 
void hammingCode(int sockfd){ 
	char buffer[80]; 
	int n; 
	while(1){ 
		bzero(buffer, sizeof(buffer)); 
        int data[10];
        printf("\nEnter bits of data one by one\n");
        scanf("%d",&data[0]);
        scanf("%d",&data[1]);
        scanf("%d",&data[2]);
        scanf("%d",&data[4]);
     
        data[6]=data[0]^data[2]^data[4];
	    data[5]=data[0]^data[1]^data[4];
	    data[3]=data[0]^data[1]^data[2];
     
	    printf("\nEncoded data is : ");
	    for(int i=0;i<7;i++){   
            buffer[i]=data[i]+48;
            printf("%d",data[i]);
        }
            
        printf("\nEncoded data is : %s", buffer); 
	    write(sockfd, buffer, sizeof(buffer)); 
	    bzero(buffer, sizeof(buffer)); 
	    read(sockfd, buffer, sizeof(buffer)); 
	    printf("\nServer>: %s", buffer); 
	    if((strcmp(buffer,"exit")) == 0){ 
		    printf("Client Exit...\n"); 
            exit(1);
            break; 
	    } 
	} 
} 
int main(){ 
	int sockfd; 
	struct sockaddr_in servAddr;  
	sockfd = socket(AF_INET, SOCK_STREAM, 0); 
	if(sockfd == -1){ 
		printf("[-]Socket could not be created\n"); 
		exit(1); 
	} 
	else{
		printf("[+]Socket successfully created!\n");
    } 
	bzero(&servAddr, sizeof(servAddr)); 
	servAddr.sin_family = AF_INET; 
	servAddr.sin_addr.s_addr = inet_addr("127.0.0.1"); 
	servAddr.sin_port = htons(4444); 
	if(connect(sockfd,(struct sockaddr *)&servAddr,sizeof(servAddr))!= 0){ 
		printf("[+]Connection to server failed\n"); 
		exit(1); 
	} 
	else{
		printf("[+]Connected to server at %s:%d\n","127.0.0.1",4444);
    }
	hammingCode(sockfd); 
	close(sockfd); 
}
