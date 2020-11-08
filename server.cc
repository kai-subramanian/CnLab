#include<iostream>
#include<sys/types.h>
#include<unistd.h>
#include<sys/socket.h>
#include<netdb.h>
#include<arpa/inet.h>
#include<string.h>
#include<string>
using namespace std;
int main(){
    //create a socket
    int listening=socket(AF_INET,SOCK_STREAM,0);
    if(listening==-1){
        cout<<"Can't create a socket :(\n";
        return -1;
    }

    //bind the socket to an ip/port
    sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(54000);
    inet_pton(AF_INET,"0.0.0.0",&hint.sin_addr);
    
    if(bind(listening,(sockaddr*)&hint,sizeof(hint)) == -1){
        cout<<"Can't create ip port :(";
        return -2;
    }

    //Mark socket to listening...
    if(listen(listening,SOMAXCONN)==-1){
        cout<<"Can't listen :(";
        return -3;    
    }
    
    //accept a call
    sockaddr_in client;
    socklen_t clientSize = sizeof(client);
    char host[NI_MAXHOST];
    char svc[NI_MAXSERV];
    int clientSocket = accept(listening,(sockaddr*)&client,&clientSize);
    if(clientSocket == -1){
        cout<<"Problem with client !";
        return -4;    
    }
    //close the listeninging socket
    close(listening);
    memset(host, 0, NI_MAXHOST);
    memset(svc,0,NI_MAXSERV);
    int result = getnameinfo((sockaddr*)&client,sizeof(client),host,NI_MAXHOST,svc,NI_MAXSERV,0);
    if(result){
        cout<<"Connected on : "<<svc<<endl;
    }
    else{
        inet_ntop(AF_INET,&client.sin_addr,host,NI_MAXHOST);
        cout<<host<<"Connected on " << ntohs(client.sin_port) << endl;    
    }
    //recieveing displayed message
    char buffer[4096];
    string cmsg = "goodbye";
    int ex;
    while(true){    
        //clear buffer 
        memset(buffer, 0, 4096);
        //wait for message
        int bytesrecd = recv(clientSocket, buffer, 4096, 0);
        if(bytesrecd == -1){
            cout<<"Connection issue"<<endl;
            break;        
        }
        if (bytesrecd == 0){
            cout<<"Client disconnected"<<endl;        
        }
        
        //display it
        string smsg = string(buffer,0,bytesrecd);
        cout<<smsg;
        if(smsg!=cmsg){
            cout<<"Continue"<<endl;
        }
        else{
           cout<<"Invalid"<<endl;
        }
        send(clientSocket, buffer,  bytesrecd+1, 0);        
    }
    cout<<"Exiting";
    //close socket.
    close(clientSocket);
    return 0;
}















