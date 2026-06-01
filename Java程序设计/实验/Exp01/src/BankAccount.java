import java.util.*;
public class BankAccount {
    private int balance;
    public BankAccount() {
        this.balance = 0;
    }

    public BankAccount(int initialBalance) {
        this.balance = initialBalance;
    }
    public int getBalance() {
        return balance;
    }
    public void withdraw(int amount) {
        if (amount > 0 && amount <= balance) {
            balance -= amount;
        } else {
            System.out.println("取款金额无效或余额不足！");
        }
    }
    public void deposit(int amount) {
        if (amount > 0) {
            balance += amount;
        } else {
            System.out.println("存款金额无效！");
        }
    }


    public static void main(String[] args) {
        Scanner scanner = new java.util.Scanner(System.in);

        int initialBalance = scanner.nextInt();
        BankAccount account = new BankAccount(initialBalance);

        int operationCount = scanner.nextInt();

        for (int i = 0; i < operationCount; i++) {
            int operationType = scanner.nextInt();
            int amount = scanner.nextInt();

            if (operationType == 1) { // 存款
                account.deposit(amount);
            } else if (operationType == 2) { // 取款
                account.withdraw(amount);
            }

            System.out.println(account.getBalance());
        }

        scanner.close();
    }
}
