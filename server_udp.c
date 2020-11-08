#include <stdio.h> 
#include <strings.h> 
#include <sys/types.h> 
#include <arpa/inet.h> 
#include <sys/socket.h> 
#include<netinet/in.h> 
#define PORT 5000 
#define MAXLINE 1000 

// Driver code 
int main() 
{ 
    //declarations and stuff
	char buffer[100]; 
	char *w1 = "An interconnection of devices using a connection media governed by protocols";
    char *w2 = "Short for wireless fidelity, used for wireless data transfer";
    char *w3 = "A guided media using copper/other conductive metal for data transfer"; 
    char *w4 = "Short for User Datagram Protocol, it is a connectionless protocol that doesn't send acknowledgement";
	int listenfd, len; 
	struct sockaddr_in servaddr, cliaddr; 
	bzero(&servaddr, sizeof(servaddr)); 
	listenfd = socket(AF_INET, SOCK_DGRAM, 0);		 
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY); 
	servaddr.sin_port = htons(PORT); 
	servaddr.sin_family = AF_INET; 

	// bind server address to socket descriptor 
	bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr)); 
	
	//receive the datagram 
	len = sizeof(cliaddr); 
	int n = recvfrom(listenfd, buffer, sizeof(buffer), 
			0, (struct sockaddr*)&cliaddr,&len); //receive message from server 
	buffer[n] = '\0'; 
	puts(buffer); 
		
	// send the response 
    if(buffer[0]=='n'){
	    sendto(listenfd, w1, MAXLINE, 0, 
		    (struct sockaddr*)&cliaddr, sizeof(cliaddr)); 
    }
    else if(buffer[0]=='w'){
        sendto(listenfd, w2, MAXLINE, 0, 
		    (struct sockaddr*)&cliaddr, sizeof(cliaddr));
    }
    else if(buffer[0]=='c'){
        sendto(listenfd, w3, MAXLINE, 0, 
		    (struct sockaddr*)&cliaddr, sizeof(cliaddr));
    }
    else if(buffer[0]=='u'){
        sendto(listenfd, w4, MAXLINE, 0, 
		    (struct sockaddr*)&cliaddr, sizeof(cliaddr));
    }
    
} 

