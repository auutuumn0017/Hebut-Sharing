import java.io.*;
import java.net.*;

public class MyServerDuo {
    public static void main(String[] args) throws IOException {
        ServerSocket ss = new ServerSocket(1234);//0-65535
        System.out.println("服务器已启动，等待客户端连接...");
        Socket s = ss.accept();//没人来就阻塞
        System.out.println("客户端已连接，IP 地址：" + s.getInetAddress().getHostAddress());

        SReadThread srt =new SReadThread(s);
        SSendThread sst=new SSendThread(s);
        srt.start();
        sst.start();
    }
}

// 接收消息线程
class SReadThread extends Thread {
    private Socket socket;

    public SReadThread(Socket socket) {
        this.socket = socket;
    }

    public void run() {
        try {
            BufferedReader in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
            String line;
            while ((line = in.readLine()) != null) {
                System.out.println("客户端说: " + line);
            }
        }
        catch (IOException e) {
            System.out.println(e.getMessage());
        }
    }
}

// 发送消息线程
class SSendThread extends Thread {
    private Socket socket;

    public SSendThread(Socket socket) {
        this.socket = socket;
    }

    public void run() {
        try {
            PrintWriter out = new PrintWriter(socket.getOutputStream(), true);
            BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
            String line;
            while ((line = br.readLine()) != null) {
                out.println(line);
            }
        }
        catch (IOException e) {
            System.out.println(e.getMessage());
        }
    }
}
