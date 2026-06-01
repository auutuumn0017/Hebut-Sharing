import java.util.*;
public class Count extends Thread{
    /*public Count(){}*///构造不用写
    public void run(){
        for(int i=1;i<=100;i++){
            if(i%2==0)
                System.out.println(i+"是偶数");
        }
    }
}
class CountJi extends Thread{
    public void run(){
        for(int j=400;j<=600;j++){
            if(j%2!=0)
                System.out.println(j+"是奇数");
        }
    }
}
class Main{
    public static void main(String args[]){
        Count c=new Count();
        CountJi cj= new CountJi();
        c.start();
        cj.start();
    }
}