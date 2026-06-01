public interface Shape {
    double getArea();//默认public abstract，抽象类中可以写abstract或者不写
    double getPerimeter();
}

class Coordinate
{ int x, y;
    Coordinate(int x, int y)
    {
        this.x=x;
        this.y=y;
    }
}

class Rectangle extends Coordinate implements Shape{
    Coordinate c;
    private double width, height;
    Rectangle(int x, int y, double width, double height){
        super(x,y);
        this.width=width;
        this.height=height;
    }

    public double getArea(){
        return width*height;
    }
    public double getPerimeter(){
        return 2*(width+height);
    }
}

class Circle extends Coordinate implements Shape{
    Coordinate c;
    private double radius;
    Circle(int x, int y, double radius){
        super(x,y);
        this.radius=radius;
    }

    public double getArea(){
        return Math.PI*radius*radius;
    }
    public double getPerimeter(){
        return 2*Math.PI*radius;
    }
}

class Triangle extends Coordinate implements Shape{
    Coordinate c;
    private double a,b,d;
    Triangle(int x, int y, int a,int b,int d){
        super(x,y);
        this.a=a;
        this.b=b;
        this.d=d;
    }

    public double getArea(){
        double s=(getPerimeter()/2);
        return Math.sqrt(s*(s-a)*(s-b)*(s-d));
    }
    public double getPerimeter(){
        return a+b+d;
    }
}

class Main_Shape{
    public static void main(String[] args) {
        Shape s1 = new Rectangle(1,1,2,3);
        Shape s2 = new Circle(1,1,2);
        Shape s3 = new Triangle(1,1,2,3,4);
        System.out.println(s1.getArea());
        System.out.println(s2.getArea());
        System.out.println(s3.getArea());
        System.out.println(s1.getPerimeter());
    }
}


