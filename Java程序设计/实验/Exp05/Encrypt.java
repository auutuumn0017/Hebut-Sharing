import java.util.*;
import java.io.*;
public class Encrypt {
    public static void main(String args[]) {
        String inputFilePath = "helloWorld.txt";
        String outputFilePath = "secret.txt";

        try {
            File inputFile = new File(inputFilePath);
            FileReader fileReader = new FileReader(inputFile);
            BufferedReader bufferedReader = new BufferedReader(fileReader);

            File outputFile = new File(outputFilePath);
            FileWriter fileWriter = new FileWriter(outputFile);
            BufferedWriter bufferedWriter = new BufferedWriter(fileWriter);

            String line;
            while ((line = bufferedReader.readLine()) != null) {
                char[] characters = line.toCharArray();
                for (int i = 0; i < characters.length; i++) {
                    char c = characters[i];
                    if (c >= 'a' && c <= 'z') {
                        characters[i] = (char) ((c - 'a' + 1) % 26 + 'A');
                    }
                    else if (c >= 'A' && c <= 'Z') {
                        characters[i] = (char) ((c - 'A' + 1) % 26 + 'a');
                    }
                }
                bufferedWriter.write(new String(characters));
                bufferedWriter.newLine();
            }

            bufferedReader.close();
            bufferedWriter.close();

            System.out.println("文件加密完成，加密后的内容已保存到 " + outputFilePath);

        } catch (IOException e) {
            System.err.println("发生错误：" + e.getMessage());
        }
    }
}