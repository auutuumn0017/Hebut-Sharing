import java.io.*;
import java.util.Scanner;

public class StudentInfoHandler {
    public static void main(String[] args) {
        String file1 = "myfile1.txt";
        String file2 = "myfile2.txt";

        try (Scanner scanner = new Scanner(System.in);
             BufferedWriter writer = new BufferedWriter(new FileWriter(file1))) {

            System.out.println("请输入学生信息（输入'bye'结束）：");
            String input;
            while (!(input = scanner.nextLine()).equalsIgnoreCase("bye")) {
                writer.write(input);
                writer.newLine();
            }

            System.out.println("学生信息已保存到 " + file1);

            // 拷贝文件
            try (BufferedReader reader = new BufferedReader(new FileReader(file1));
                 BufferedWriter writer2 = new BufferedWriter(new FileWriter(file2))) {

                String line;
                while ((line = reader.readLine()) != null) {
                    writer2.write(line);
                    writer2.newLine();
                }

                System.out.println("文件内容已拷贝到 " + file2);
            }

        } catch (IOException e) {
            System.err.println("Error: " + e.getMessage());
        }
    }
}