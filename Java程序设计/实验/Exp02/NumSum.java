import java.util.*;

public class NumSum {
    public static void main(String[] args) {
        Scanner scan = new Scanner(System.in);
        String input = scan.nextLine();
        String[] elements = input.split(" ");// 按空格分割输入的字符串
        //split()依据指定的分隔符把一个字符串分割成多个子字符串，最终返回一个字符串数组。
        int sum = 0;
        for (String element : elements) {
            try {
                // 尝试将元素转换为整数
                int num = Integer.parseInt(element);
                // 如果转换成功，累加到总和中
                sum += num;
            }
            catch (NumberFormatException e) {
                // 如果转换失败，说明是字母，忽略该元素
            }
        }
        // 输出结果
        System.out.println("Sum=" + sum);
    }
}
