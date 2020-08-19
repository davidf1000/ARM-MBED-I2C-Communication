# ARM-MBED-I2C-Communication
Simple starting code for both slave and master ARM-based microcontroller to be able to communicate with each other via I2C Protocol. Communication doesn't have to be periodical because comm is triggered with interrupt.

## PinOut 
SLAVE   -   MASTER <br>
PB_9    -   PB-9    (SDA) with pullup  <br>
PB_8    -   PB_8    (SCL) with pullup <br> 
PC_8    -   PC_8    (Interrupt) <br>
GND     -   GND <br>

## Performance 
Udah ditesting dan hasilnya cukup cepat, rate kirimnya byte/sec belom ada tapi utk sanggup untuk kirim
12 Byte String setiap 0.02 detik di loop, kalau delay 0.01 detik kebawah slave kewalahan dan gak sanggup nerima data full . 
Kalo pesan makin sedikit pasti makin cepet.


