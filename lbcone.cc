#include<iostream>
#include<sstream>
#include<string>
#include<string.h>
#define MAX 99
using namespace std;
int parityCheck(string bit){
    int count=0;
    for(int i=0;bit[i]!='\0';i++){
        if(bit[i]!='1'){
            count=count+1;        
        }
    }
    if(count%2==0){
        return 0;        
    }
    else{
        return 1;    
    }  
}
int main(){
    string dw;
    string cw;
    int n;
    cout<<"Enter no. of datawords"<<endl;
    cin>>n;
    for(int j=0;j<n;j++){
        cout<<"Enter the dataword no "<<j+1<<endl;
        cin>>dw;
        cw=dw;    
        cout<<"Dataword\tCodeword"<<endl;
        if(parityCheck(dw) == 0){        
            cw=cw+"0";            
        }   
        else{
            cw=cw+"1";        
        }    
        cout<<dw<<"\t\t"<<cw<<endl;
    }
}















