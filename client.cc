#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>
#include <fstream>
using namespace std;
int main(){
    //Create a socket
    int sck = socket(AF_INET, SOCK_STREAM, 0);
    if (sck == -1){
        return 1;
    }

    //Create a hint structure for the server we're connecting with
    int port = 54000;
    string ipadd = "127.0.0.1";
    sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(port);
    inet_pton(AF_INET, ipadd.c_str(), &hint.sin_addr);

    //Connect to the server on the socket
    int connect_res = connect(sck, (sockaddr*)&hint, sizeof(hint));
    if (connect_res == -1){
        return 1;
    }

    char buffer[4096];
    cout<<"Enter the filename to display: ";
    cin>>buffer;
    write(sck,buffer,100);
    cout<<"Sent successfully: "<<buffer<<"\n";
    read(sck,buffer,100);
    cout<<"Contents are: "<<buffer<<"\n";
    //Close the socket
    close(sck);

    return 0;
}
