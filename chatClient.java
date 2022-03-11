import java.io.*;
import java.net.*;

public class chatClient {
    public static void main(String[] args) throws Exception {
        Socket s=new Socket("127.0.0.1",5500);
        System.out.println("Connected to localhost server, on port 5500");
        
        OutputStream os=s.getOutputStream();
        InputStream is=s.getInputStream();
        
        BufferedReader keyRead=new BufferedReader(new InputStreamReader(System.in));
        BufferedReader receiveRead=new BufferedReader(new InputStreamReader(is));
        
        PrintWriter pw=new PrintWriter(os,true);

        System.out.println("Start the chat. Press enter to send. Say Hi !");
        String receivedMsg, sentMsg;

        while(true){
            System.out.print(">");
            sentMsg=keyRead.readLine();
            pw.println(sentMsg);
            pw.flush();
            receivedMsg=receiveRead.readLine();
            if(receivedMsg!=null){
                System.out.println(receivedMsg);
            }
        }
    }    
}