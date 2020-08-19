/* mbed Example Program
DEMO terima data dari master, di main() cuma increment & print"an. Kalo ada data masuk langsung ke interrupt terus 
data disimpen di variable global dataakhir
 */
#include <mbed.h>
#if !DEVICE_I2CSLAVE
#error[NOT_SUPPORTED] I2C Slave is not supported
#endif
volatile float tes;
char dataakhir[50];


int idx;
bool cond;
InterruptIn atas(PC_8);
I2CSlave slave(PB_9, PB_8);
Serial pc(SERIAL_TX, SERIAL_RX);

// Read single char from I2C Line
char readi2c()
{
    char buf[1];
    if(slave.receive()==I2CSlave::WriteAddressed) {
        slave.read(buf, 1);
        return buf[0];
    }
    for (int i = 0; i < 10; i++)
        buf[i] = 0; // Clear buffer
    return '~';
}
// Callbacked when interrupt, read whole string from I2C Line 
void getData()
{

    char read;
    read = readi2c();
    if (read != '~') {
        if (cond) {
            if (read=='>') {
                cond = 0;
                dataakhir[idx] = '\0';
                pc.printf("[ string : %s ]\n", dataakhir);
                for (int i = 0; i < 10; i++)
                    dataakhir[i] = 0;
                idx = 0;

            }
            dataakhir[idx] = read;
            idx++;
        }
        if (read == '<') {
            cond = 1;
            idx = 0;

        }
    }
}
int main()
{
    cond = 0;
    atas.rise(&getData);
    slave.address(0x50);
    pc.printf("Slave Demo \nWill Receive incoming I2C msg from Top Nucleo\n");
    int i = 0;
    while (1) {
        i++;
        pc.printf(".");
        wait(0.1);
    }
}