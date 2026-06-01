import java.io.*;
import java.net.*;

public class MyClientDuo {
    public static void main(String[] args) throws IOException {
        Socket s = new Socket("127.0.0.1",1234);//端口号一样才能连接上
        CReadThread crt =new CReadThread(s);
        CSendThread cst=new CSendThread(s);
        crt.start();
        cst.start();
    }
}

class CReadThread extends Thread {
    private Socket socket;

    public CReadThread(Socket socket) {
        this.socket = socket;
    }

    public void run() {
        try {
            BufferedReader in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
            String line;
            while ((line = in.readLine()) != null) {
                System.out.println("服务器说: " + line);
            }
        } catch (IOException e) {
            System.out.println(e.getMessage());
        }
    }
}

class CSendThread extends Thread {
    private Socket socket;

    public CSendThread(Socket socket) {
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
        } catch (IOException e) {
            System.out.println(e.getMessage());
        }
    }
}
