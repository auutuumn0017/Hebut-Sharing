import java.util.*;
//构造函数参数顺序得规范，不然影响后面
//现在发现这个做麻烦了，直接在构造函数里面检查异常即可，没必要在set函数里面检查，可以看Loan.java
//哪里用了异常类，他的父类也得有异常检查
public class MyDate {
    private int day,month,year;
    public MyDate(){}
    public MyDate(int year,int month,int day) throws DateException{
        this.setYear(year);
        this.setMonth(month);
        this.setDay(day);
    }

    public int m[]={0,31,28,31,30,31,30,31,31,30,31,30,31};
    public void DayofMonth(){
        if(year%4==0&&year%100!=0||year%400==0)
            m[2]=29;
    }

    public int getDay() {
        return day;
    }
    public void setDay(int day) throws DateException {
        if(day>m[month]||day<1)
            throw new DateException("日期必须在1-"+m[month]+"之间");
        else
            this.day=day;
    }

    public int getMonth() {
        return month;
    }
    public void setMonth(int month) throws DateException {
        if(month>12||month<1)
            throw new DateException("月份必须在1-12之间");
        else
            this.month=month;
    }

    public int getYear() {
        return year;
    }
    public void setYear(int year) throws DateException{
        if(year<0)
            throw new DateException("年份必须大于0");
        else {
            this.year = year;
            DayofMonth();
        }
    }

    public String toString(){
        return year+"/"+month+"/"+day;
    }

    public static void main(String[] args) {
        Scanner scan=new Scanner(System.in);
        while (true) {
            try{
                int year=scan.nextInt();
                int month=scan.nextInt();
                int day=scan.nextInt();
                MyDate d=new MyDate(year,month,day);
                System.out.println(d.toString());
                break;
            }
            catch (DateException e) {
                System.out.println("输入的日期不合法：" + e.getMessage());
                System.out.println("请重新输入！");
            }
            catch (InputMismatchException e) {
                System.out.println("输入格式错误，请重新输入！");
                scan.nextLine(); // 清空输入缓冲区，跳过当前行的剩余内容
            }
            catch (Exception e) {
                System.out.println("未知错误：" + e.getMessage());
            }
        }
    }
}

