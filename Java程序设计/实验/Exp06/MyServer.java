import java.net.*;
import java.io.*;
import java.util.*;
//非一问一答
public class MyServer {
    public static void main(String args[]){
        try{
            ServerSocket ss = new ServerSocket(1234);//0-65535
            System.out.println("服务器已启动，等待客户端连接...");
            Socket s = ss.accept();//没人来就阻塞
            System.out.println("客户端已连接，IP 地址：" + s.getInetAddress().getHostAddress());
            PrintStream out= new PrintStream(s.getOutputStream());
            BufferedReader in = new BufferedReader(new InputStreamReader(s.getInputStream()));
            Scanner scan =new Scanner(System.in);

            out.println("Hi，你好，欢迎连接到服务器上!请输入密码：");
            String sin,sout;
            int count=0;//记录密码错误次数
            while(count<3){
                sout=in.readLine();
                if(!sout.equals("10086")) {
                    count++;
                    out.println("输入的密码不正确，请重新输入！");
                }
                else{
                    out.println("密码验证通过!");
                    break;
                }
            }


            if(count>=3){
                out.println("密码错误次数多于3次，退出登录！");
                out.flush();  // 确保消息发出
                out.close();
                in.close();
                s.close();
                ss.close();
                return;
            }
            else{
                while(true){
                    sin=in.readLine();
                    System.out.println("客户端说: " + sin);
                    sout=scan.nextLine();//这是读一行，next只能读一个单词
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

        }
        catch(IOException e){
            System.out.println(e.getMessage());
        }
    }
}
