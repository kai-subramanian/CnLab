#include <stdio.h> 
#include <netdb.h> 
#include <netinet/in.h> 
#include <stdlib.h> 
#include <string.h> 
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h> 
#include <sys/types.h> 
void hammingCode(int sockfd){ 
	char buffer[64]; 
	int n;
    int data[10];
    int data_serv[10];
    int x,x1,x2,x3; 
	while(1){ 
		bzero(buffer,64);  
		read(sockfd,buffer,sizeof(buffer));  
		printf("From client: %s\t", buffer); 
        for(int i=0;i<7;i++){
            data_serv[i] = buffer[i];
        }     
        x1=data_serv[6]^data_serv[4]^data_serv[2]^data_serv[0];
	    x2=data_serv[5]^data_serv[4]^data_serv[1]^data_serv[0];
	    x3=data_serv[3]^data_serv[2]^data_serv[1]^data_serv[0];
	    x=(x3*4)+(x2*2)+(x1);
        if(x==0){
		    printf("\nNo error\n");
            char s[100] = "No Error ";
            write(sockfd,s,sizeof(s));
        }
	    else{
		    printf("\nError");
            char s[100] = "Error ";
            write(sockfd,s,sizeof(s));
		}
	}
}
int main() { 
	int sockfd, newfd, addrSize; 
	struct sockaddr_in servAddr;
    struct sockaddr_in cliAddr;  
	sockfd = socket(AF_INET, SOCK_STREAM, 0); 
	if(sockfd<0){ 
		printf("[-]Socket not created\n"); 
		exit(1); 
	} 
	else{
		printf("[+]Socket successfully created\n");
    } 
	bzero(&servAddr, sizeof(servAddr)); 
	servAddr.sin_family = AF_INET; 
	servAddr.sin_addr.s_addr = inet_addr("127.0.0.1"); 
	servAddr.sin_port = htons(4444); 
 
	if((bind(sockfd,(struct sockaddr *)&servAddr, sizeof(servAddr)))!=0){ 
		printf("[-]Socket could not be binded\n"); 
		exit(1); 
	} 
	else{
		printf("[+]Socket successfully binded!\n");
    }  
	if((listen(sockfd, 5)) != 0){ 
		printf("[-]Listen failed !\n"); 
		exit(1); 
	} 
	else{
		printf("[+]Server listening\n");
    } 
	addrSize=sizeof(cliAddr); 
	newfd=accept(sockfd,(struct sockaddr *)&cliAddr, &addrSize); 
	if(newfd<0){ 
		printf("[-]Server did not accept!\n"); 
		exit(1); 
	} 
	else{
		printf("[+]Client connected on %s:%d\n","127.0.0.1",4444);
    }
	hammingCode(newfd);
	close(sockfd); 
}
