import java.io.*;
import java.util.Scanner;
public class Student {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        String line;

        // 写入到myfile1.txt
        try {
            FileWriter fout = new FileWriter("myfile1.txt");
            BufferedWriter bout = new BufferedWriter(fout);
            System.out.println("请输入学生信息（格式：学号 姓名 专业 班级 家庭住址），输入bye结束：");
            while (!(line = scanner.nextLine()).equals("bye")) {
                bout.write(line);
                bout.newLine();
            }
            bout.close();
            fout.close();
        } catch (IOException e) {
            System.out.println(e.getMessage());
        }

        // 使用 FileReader 和 FileWriter 拷贝myfile1.txt内容到myfile2.txt
        try {
            FileReader fin=new FileReader("myfile1.txt");
            BufferedReader bin=new BufferedReader(fin);
            FileWriter fout=new FileWriter("myfile2.txt");
            BufferedWriter bout=new BufferedWriter(fout);

            while ((line = bin.readLine()) != null) {
                bout.write(line);
                bout.newLine();
            }
            bin.close();
            fin.close();
            bout.close();
            fout.close();
        } catch (IOException e) {
            System.out.println(e.getMessage());
        }

        // 使用 FileInputStream 和 FileOutputStream 拷贝myfile1.txt内容到myfile3.txt
        try {
            FileInputStream fis =new FileInputStream("myfile1.txt");
            FileOutputStream fos=new FileOutputStream("myfile3.txt");

            /*int data;
            while ((data = fis.read()) != -1) {
                fos.write(data);
            }*/
            byte[] buffer = new byte[1024];//这样为了一次读取多个字节
            int bytesRead;
            while ((bytesRead = fis.read(buffer)) != -1) {
                fos.write(buffer, 0, bytesRead);
            }

            fos.close();
            fis.close();
        } catch (IOException e) {
            System.out.println(e.getMessage());
        }
    }
}
