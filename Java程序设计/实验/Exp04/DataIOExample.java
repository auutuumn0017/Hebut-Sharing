import java.io.DataOutputStream;
import java.io.DataInputStream;
import java.io.FileOutputStream;
import java.io.FileInputStream;
import java.io.IOException;
import java.util.Scanner;

public class DataIOExample {
    public static void main(String[] args) {
        String fileName = "data.dat";

        // 输入数据
        try (DataOutputStream out = new DataOutputStream(new FileOutputStream(fileName))) {
            Scanner scanner = new Scanner(System.in);

            System.out.print("请输入一个整数: ");
            int intValue = scanner.nextInt();
            out.writeInt(intValue);

            System.out.print("请输入一个双精度数: ");
            double doubleValue = scanner.nextDouble();
            out.writeDouble(doubleValue);

            scanner.nextLine(); // 清除换行符
            System.out.print("请输入一个字符串: ");
            String stringValue = scanner.nextLine();
            out.writeUTF(stringValue);

            System.out.println("数据已写入文件 " + fileName);

        } catch (IOException e) {
            System.err.println("Error writing data: " + e.getMessage());
        }

        // 读取数据
        try (DataInputStream in = new DataInputStream(new FileInputStream(fileName))) {
            int intValue = in.readInt();
            double doubleValue = in.readDouble();
            String stringValue = in.readUTF();

            System.out.println("读取的数据:");
            System.out.println("整数: " + intValue);
            System.out.println("双精度数: " + doubleValue);
            System.out.println("字符串: " + stringValue);

        } catch (IOException e) {
            System.err.println("Error reading data: " + e.getMessage());
        }
    }
}