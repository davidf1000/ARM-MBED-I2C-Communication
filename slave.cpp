#include <mbed.h>

#if !DEVICE_I2CSLAVE
  #error [NOT_SUPPORTED] I2C Slave is not supported
#endif
volatile float tes;
char dataakhir[10];
char buf[10];
int idx;
char msg[] = "Slave!";
int data;
bool cond;

InterruptIn atas(PC_8);
I2CSlave slave(PB_9, PB_8);

Serial pc(SERIAL_TX, SERIAL_RX);
Timer t1;
char readi2c()
{
        char sent;
    //pc.printf("waiting for input");
          pc.printf("\n");
       int i = slave.receive();
       //pc.printf("received :%d ",i);
       switch (i) {
           case I2CSlave::ReadAddressed:
               slave.write(msg, strlen(msg) + 1); // Includes null char
               break;
           case I2CSlave::WriteGeneral:
               slave.read(buf, 10);
               pc.printf("Read G: %s\n", buf);
               break;
           case I2CSlave::WriteAddressed:
               slave.read(buf,1);
               //data = slave.read();
               //pc.printf("Read : %s|| \n", buf);
               //pc.printf(" ");
               //pc.printf("Read byte: %d\n", data);
               //pc.printf(" ");
               return buf[0];
       }
       for(int i = 0; i < 10; i++) buf[i] = 0;    // Clear buffer
       return '~';
       //pc.printf("char : %c \n",sent);
       //return sent;
   }
void getData()
{
    char read;
    char start='x';
    int datacount;
    read=readi2c();
    pc.printf("ch:|%c|\n",read);
    if(read != '~')
    {
        if (cond)
        {
            //pc.printf("get into cond\n");
            //pc.printf("idx : %d\n",idx);
            //read=readi2c();
            //pc.printf("dataakhir[idx] : %c\n",read);
            dataakhir[idx]=read;
            
            idx++;
            if(idx==5)
            {
                cond=0;
                dataakhir[strlen(dataakhir)]='\0';
                pc.printf("final string : %s\n",dataakhir);
                for(int i = 0; i < 10; i++) dataakhir[i] = 0; 
                idx=0;
                 t1.stop();
                 pc.printf("delay between read: %f \n",t1.read()-tes);
                 tes= t1.read();
                 t1.start();
                
            }     
        }
        
        if (read==start)
        {
            pc.printf("start! \n");
            cond=1;
            idx=0;
        }

    

    }
}
void call()
{
    //pc.printf("got into intterupt \n");
    //t1.stop();
    //pc.printf("delay between read: %f \n",t1.read()-tes);
    //tes= t1.read();
    //t1.start();
    //while(slave.receive()==0)
    //readi2c();
    getData();
    //readi2c();

}
int main() {
   cond=0;
    atas.rise(&call);
    t1.start();    
   slave.address(0x50<<1);
   pc.printf("starting program");
   //slave.frequency(100000);
   int i=0;
   while (1) {
          i++;

          //pc.printf("looping %d\n",i);
}
}