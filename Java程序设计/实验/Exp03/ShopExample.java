class Shop implements Runnable
{
    Thread zhangWorker, wangWorker, boss;
    public Shop()
    {
        boss = new Thread(this);
        zhangWorker = new Thread(this);
        wangWorker = new Thread(this);
        boss.setName("老板");
        zhangWorker.setName("张工");
        wangWorker.setName("王工");
    }
    public void run()
    {
        int i=0;
        if (Thread.currentThread()==zhangWorker)
        {
            while (true)
            {
                try { i++;
                    System.out.printf("\n%s 已搬运了%d 箱苹果\n",zhangWorker.getName(),i);
                    if (i==3)
                        return;
                    Thread.sleep(5000);
                }
                catch(InterruptedException e)
                {
                    System.out.printf("\n%s 让 %s 继续工作",boss.getName(),zhangWorker.getName(),i);
                }
            }
        }
        else if (Thread.currentThread()==wangWorker)
        {
            while (true )
            {
                try { i++;
                    System.out.printf("\n%s 已搬运了%d 箱香蕉\n",wangWorker.getName(),i);
                    if (i==3)
                        return ;
                    Thread.sleep(5000);
                }
                catch(InterruptedException e)
                {
                    System.out.printf("\n%s 让 %s 继续工作",boss.getName(),wangWorker.getName(),i);
                }
            }
        }
        else if (Thread.currentThread()==boss)
        {
            while (true)
            {
                synchronized (this) {
                    notifyAll(); // 唤醒所有等待的工人
                }
                if (!(wangWorker.isAlive()|| zhangWorker.isAlive()))
                {
                    System.out.printf("%n%s 下班",boss.getName());
                    return;
                }
            }
        }
    }
}
public class ShopExample
{
    public static void main(String a[])
    {
        Shop shop=new Shop();
        shop.boss.start();
        shop.zhangWorker.start();
        shop.wangWorker.start();
    }
}