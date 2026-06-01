import java.io.*;

public class EncryptTextFile {
    public static void main(String[] args) {
        String inputFile = "helloWorld.txt";
        String outputFile = "secret.txt";

        try (BufferedReader reader = new BufferedReader(new FileReader(inputFile));
             BufferedWriter writer = new BufferedWriter(new FileWriter(outputFile))) {

            String line;
            while ((line = reader.readLine()) != null) {
                String encryptedLine = encrypt(line);
                writer.write(encryptedLine);
                writer.newLine();
            }

            System.out.println("File encrypted successfully!");

        } catch (IOException e) {
            System.err.println("Error: " + e.getMessage());
        }
    }

    private static String encrypt(String text) {
        StringBuilder encrypted = new StringBuilder();
        for (char c : text.toCharArray()) {
            if (Character.isUpperCase(c)) {
                encrypted.append((char) ('Z' - (c - 'A')));
            } else if (Character.isLowerCase(c)) {
                encrypted.append((char) ('z' - (c - 'a')));
            } else {
                encrypted.append(c);
            }
        }
        return encrypted.toString();
    }
}