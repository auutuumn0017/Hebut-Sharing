public class Person {
    protected String name;//记得让子类能用
    protected int age;
    protected char sex;
    Person(){}
    Person(String name,int age,char sex){
        this.name=name;
        this.age=age;
        this.sex=sex;
    }

    public String show(){
        return "姓名："+name+" 年龄："+age+" 性别："+sex;
    }
}

class Student extends Person{
    private int id;
    Student(String name,int age,char sex,int id){
        super(name,age,sex);
        this.id=id;
    }
    public String show(){
        return "姓名："+name+" 年龄："+age+" 性别："+sex+" 学号："+id;
    }
}

class Main{
    public static void main(String[] args) {
        Person p=new Person("jennie",20,'女');
        System.out.println(p.show());
        Student s=new Student("jisoo",21,'女',1001);
        System.out.println(s.show());
    }
}
