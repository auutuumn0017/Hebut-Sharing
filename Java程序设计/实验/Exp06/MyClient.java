import java.net.*;
import java.io.*;
import java.util.*;
//建立Socket
//打开输入输出流
//通信
//关闭输入输出流和Socket

//一问一答
public class MyClient {
    public static void main(String args[]){
        try{
            Socket s = new Socket("127.0.0.1",1234);//端口号一样才能连接上
            PrintStream out= new PrintStream(s.getOutputStream());
            BufferedReader in = new BufferedReader(new InputStreamReader(s.getInputStream()));//字节变字符再Buffered
            Scanner scan =new Scanner(System.in);

            String sin,sout;
            sin=in.readLine();
            if(!sin.equals("Hi，你好，欢迎连接到服务器上!请输入密码：")){
                out.close();
                in.close();
                s.close();
            }
            else{
                System.out.println("请输入密码 ");
                int attempt=0;
                while (true) {
                    sout = scan.nextLine();
                    out.println(sout);
                    sin = in.readLine();

                    if (sin.equals("密码验证通过!")) {
                        System.out.println("用户验证通过 ");

                        System.out.print("请发送第一条消息: ");
                        sout = scan.nextLine();
                        out.println(sout);

                        while (true) {
                            // 然后等待服务器回复
                            sin = in.readLine();
                            if(sin == null || sin.equals("bye")) {
                                System.out.println("通信结束！");
                                break;
                            }

                            System.out.println("服务器说: " + sin);
                            System.out.print("请回复: ");
                            sout = scan.nextLine();
                            out.println(sout);

                            if(sout.equals("bye")) {
                                System.out.println("通信结束！");
                                break;
                            }
                        }

                        out.close();
                        in.close();
                        s.close();
                        break;
                    }
                    else if (sin.equals("密码错误次数多于3次，退出登录！")) {
                        System.out.println("密码错误次数多于3次，退出登录！");
                        out.close();
                        in.close();
                        s.close();
                        return;
                    }
                    else {
                        System.out.println("输入的密码不正确，请重新输入！");
                        attempt++;
                        if(attempt >= 3) {
                            System.out.println("密码错误次数超过3次，连接已关闭");
                            out.close();
                            in.close();
                            s.close();
                            return;
                        }
                    }
                }
            }

        }
        catch(IOException e){
            System.out.println(e.getMessage());
        }
    }
}
