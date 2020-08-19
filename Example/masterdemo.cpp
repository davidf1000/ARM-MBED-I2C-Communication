/* mbed Example Program
DEMO Kirim data string 12 bytes.
untuk contoh msg 12 bytes, delay minimum antar pesan 0.02 s/ 20 ms
i2c delay supaya pin interrupt output punya waktu untuk rising dari 0 ke 1 supaya kedetect oleh slave 
 */
#include "mbed.h"
DigitalOut interrupt(PC_8);
Serial pc(SERIAL_TX, SERIAL_RX);
I2C i2c(PB_9, PB_8);

const float i2cdelay = 0.0001;
const int addr8bit = 0x50;
void sentChar(char x)
{
    char datasent[1];
    interrupt = 0;
    datasent[0] = x;
    i2c.write(addr8bit, datasent, 1);
    interrupt = 1;
    wait(i2cdelay);
}
void sent(char *data)
{
    //SENT starter char first
    sentChar('<');
    for (int i = 0; i < strlen(data); i++)
    {
        sentChar(data[i]);
    }
    sentChar('>');
}
int main()
{
    interrupt = 0;
    wait(1);
    const float delay = 0.1;
    while (1)
    {
        sent("1st message!");
        pc.printf("1st SENT ! \n");
        wait(delay);
        sent("2nd message!");
        pc.printf("2nd SENT ! \n");
        wait(delay);
        sent("3rd message!");
        pc.printf("3rd SENT ! \n");
        wait(delay);
        sent("4th message!");
        pc.printf("4th SENT ! \n");
        wait(delay);
        wait(2);
    }
}