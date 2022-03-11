import java.io.*;
import java.net.*;

public class chatServer{
    public static void main(String[] args) throws Exception {
        ServerSocket ss=new ServerSocket(5500);
        System.out.println("Server connected on port 5500, ready for chatting");
        Socket s=ss.accept();
        
        OutputStream os=s.getOutputStream();
        InputStream is=s.getInputStream();
        
        BufferedReader keyReader = new BufferedReader(new InputStreamReader(System.in));
        BufferedReader receiveRead = new BufferedReader(new InputStreamReader(is));

        PrintWriter pw=new PrintWriter(os,true);
        
        String recievedMsg="";
        String sendMsg="";
        
        while(true){
            System.out.print(">");
            recievedMsg = receiveRead.readLine();
            if(recievedMsg!=null){
                System.out.println(recievedMsg);
            }
            sendMsg=keyReader.readLine();
            pw.println(sendMsg);
            pw.flush();
        }
    }
}