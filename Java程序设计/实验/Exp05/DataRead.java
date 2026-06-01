import java.io.*;
import java.util.Scanner;
public class DataRead {
    public static void main(String args[]){
        Scanner scan =new Scanner(System.in);
        System.out.println("请分别输入一个整型，一个双精度型和一个字符串：");
        int a=scan.nextInt();
        double b=scan.nextDouble();
        String c=scan.next();

        try {
            FileOutputStream fin = new FileOutputStream("task3.txt");
            DataOutputStream din = new DataOutputStream(fin);
            din.writeInt(a);
            din.writeDouble(b);
            din.writeUTF(c);
            din.close();
            fin.close();
        }
        catch(IOException e){
            System.out.println("文件不存在");
        }

        try{
            FileInputStream fout = new FileInputStream("task3.txt");
            DataInputStream dout = new DataInputStream(fout);
            System.out.println(dout.readInt());
            System.out.println(dout.readDouble());
            System.out.println(dout.readUTF());
            dout.close();
            fout.close();
            System.out.println("文件读取成功");
        }
        catch(IOException e){
            System.out.println("文件不存在");
        }
    }
}
