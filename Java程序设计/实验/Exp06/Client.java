import java.net.*;
import java.io.*;
import java.util.*;
 //建立Socket
 //打开输入输出流
 //通信
 //关闭输入输出流和Socket

//一问一答
public class Client {
    public static void main(String args[]){
        try{
            Socket s = new Socket("127.0.0.1",1234);//端口号一样才能连接上
            PrintStream out= new PrintStream(s.getOutputStream());
            BufferedReader in = new BufferedReader(new InputStreamReader(s.getInputStream()));//字节变字符再Buffered
            Scanner scan =new Scanner(System.in);

            String sin,sout;
            while(true){
                sin=in.readLine();
                System.out.println("服务器说: " + sin);
                sout=scan.nextLine();
                out.println(sout);
                if((sin.equals("bye") || sout.equals("bye"))){
                    System.out.println("通信结束！");
                    break;
                }
            }
        }
        catch(IOException e){
            System.out.println(e.getMessage());
        }
    }
}
