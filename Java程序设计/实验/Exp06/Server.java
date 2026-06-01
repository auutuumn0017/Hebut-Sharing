import java.net.*;
import java.io.*;
import java.util.*;
//一问一答
public class Server {
    public static void main(String args[]){
        try{
            ServerSocket ss = new ServerSocket(1234);//0-65535
            System.out.println("服务器已启动，等待客户端连接...");
            Socket s = ss.accept();//没人来就阻塞
            System.out.println("客户端已连接，IP 地址：" + s.getInetAddress().getHostAddress());
            PrintStream out= new PrintStream(s.getOutputStream());
            BufferedReader in = new BufferedReader(new InputStreamReader(s.getInputStream()));
            Scanner scan =new Scanner(System.in);

            out.println("欢迎光临本聊天室！");//这是给客户端发消息
            String sin,sout;
            while(true){
                sin=in.readLine();
                System.out.println("客户端说: " + sin);
                sout=scan.nextLine();
                out.println(sout);
                if((sin.equals("bye") || sout.equals("bye"))){
                    System.out.println("通信结束！");
                    break;
                }
            }

            out.close();
            in.close();
            s.close();
            ss.close();
        }
        catch(IOException e){
            System.out.println(e.getMessage());
        }
    }
}
