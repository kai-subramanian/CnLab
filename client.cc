#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>
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

    //While loop:
    char buffer[4096];
    string user_ip;

    while(true){
        //Enter lines of text
        cout << "> ";
        getline(cin, user_ip);

        //Send to server
        int send_msg = send(sck, user_ip.c_str(), user_ip.size() + 1, 0);
        if (send_msg == -1){
            cout << "Could not send to server! Whoops!\r\n";
            continue;
        }
        string cmsg="goodbye";
        //Wait for response
        memset(buffer, 0, 4096);
        int bytesrecd = recv(sck, buffer, 4096, 0);
        if (string(buffer,bytesrecd)==cmsg){
            cout<<"Invalid"<<endl;        
        }
        
        else if (bytesrecd == -1){
            cout << "There was an error getting response from server\r\n";
        }
        
        else{
                        //Display response
            cout << "SERVER> " << string(buffer, bytesrecd) << "\r\n";        
        }

    }

    //Close the socket
    close(sck);

    return 0;
}
