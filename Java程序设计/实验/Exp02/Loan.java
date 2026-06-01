import java.util.*;
public class Loan {
    private double monthlyInterestRate;//贷款月利率
    private int numberOfYears;//贷款年数
    private double loanAmount;//贷款额

    public Loan(){}
    public Loan(double monthlyInterestRate,int numberOfYears,double loanAmount){
        if (numberOfYears <= 0) {
            throw new IllegalArgumentException("Number of years must be positive");
        }
        if (monthlyInterestRate <= 0) {
            throw new IllegalArgumentException("Annual interest rate must be positive");
        }
        if (loanAmount <= 0) {
            throw new IllegalArgumentException("Loan amount must be positive");
        }
        this.monthlyInterestRate=monthlyInterestRate;
        this.numberOfYears=numberOfYears;
        this.loanAmount=loanAmount;
    }

    public double getMonthlyInterestRate(){
        return monthlyInterestRate;
    }
    public void setMonthlyInterestRate(double monthlyInterestRate){
        this.monthlyInterestRate=monthlyInterestRate;
    }

    public int getNumberOfYears(){
        return numberOfYears;
    }
    public void setNumberOfYears(int numberOfYears){
        this.numberOfYears=numberOfYears;
    }

    public double getLoanAmount(){
        return loanAmount;
    }
    public void setLoanAmount(double loanAmount){
        this.loanAmount=loanAmount;
    }

    public double getMothlyPayment(){
        return  loanAmount*monthlyInterestRate/(1-1/Math.pow(1+monthlyInterestRate,numberOfYears*12));
    }
    public double getTotalPayment(){
        return getMothlyPayment()*numberOfYears*12;
    }


    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
        while (input.hasNext()) {
            double AIR = input.nextDouble();
            int NOY = input.nextInt();
            double LA = input.nextDouble();
            try {
                Loan m = new Loan(AIR, NOY, LA);
                System.out.printf("%.3f\n",m.getTotalPayment());
            }
            catch (Exception e) {
                System.out.println(e);
            }
        }

    }
}



