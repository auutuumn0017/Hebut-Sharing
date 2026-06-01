import java.util.*;
public class MyDate {
    private int day,month,year;
    public MyDate(){}
    public MyDate(int day,int month,int year) {
        this.day=day;
        this.month=month;
        this.year=year;
    }

    public int getDay() {
        return day;
    }
    public void setDay(int day) {
        this.day=day;
        if(day>31||day<1)
            System.out.println("输入无效");
    }

    public int getMonth() {
        return month;
    }
    public void setMonth(int month) {
        this.month=month;
        if(month>12||month<1)
            System.out.println("输入无效");
    }

    public int getYear() {
        return year;
    }
    public void setYear(int year) {
        this.year=year;
        if(year<0)
            System.out.println("输入无效");
    }

    public String toString(){
        return year+"/"+month+"/"+day;
    }

    public static void main(String[] args) {
        Scanner scan=new Scanner(System.in);
        int year=scan.nextInt();
        int month=scan.nextInt();
        int day=scan.nextInt();
        MyDate d=new MyDate(day,month,year);
        System.out.println(d.toString());
    }
}

