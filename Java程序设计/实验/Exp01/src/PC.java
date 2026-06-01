class CPU{
    private int speed;
    CPU(int speed){
        this.speed=speed;
    }
    public void setSpeed(int speed){
        this.speed=speed;
    }
    public int getSpeed(){
        return speed;
    }
}

class HardDisk{
    private int amount;
    HardDisk(int amount){
        this.amount=amount;
    }
    public void setAmount(int amount){
        this.amount=amount;
    }
    public int getAmount(){
        return amount;
    }
}

public class PC {
    private CPU cpu;
    private HardDisk hd;
    PC(){

    }
    PC(CPU cpu,HardDisk hd){
        this.cpu=cpu;
        this.hd=hd;
    }

    public void setCPU(CPU cpu){
        this.cpu=cpu;
    }
    public void setHD(HardDisk hd){
        this.hd=hd;
    }

    public void show(){
        System.out.println("CPU的速度为："+cpu.getSpeed());
        System.out.println("硬盘容量为："+hd.getAmount());
    }
}

class Test{
    public static void main(String args[]){
        CPU c=new CPU(2000);
        HardDisk disk=new HardDisk(200);
        PC pc=new PC();
        pc.setHD(disk);
        pc.setCPU(c);
        pc.show();
    }
}
