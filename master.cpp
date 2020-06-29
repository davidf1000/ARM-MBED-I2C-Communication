/* mbed Example Program
 * Copyright (c) 2006-2014 ARM Limited
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include "mbed.h"
 DigitalOut interrupt(PC_8);
// Read temperature from LM75BD

I2C i2c(PB_9 , PB_8 ); 

//const int addr7bit = 0x50;      // 7 bit I2C address
const int addr8bit = 0x50 << 1; // 8bit I2C address, 0x90
void sent(char data[10])
{
   char    datasent[1];
   //SENT starter char first
        interrupt = 0; 
        datasent[0]='x';
        
        interrupt = 1; 
        i2c.write(addr8bit, datasent, 1 );
         wait(0.06);
   for(int i=0 ;i<5;i++)
        {
        interrupt = 0; 
        datasent[0]=data[i];
        
        interrupt = 1; 
        i2c.write(addr8bit, datasent, 1 );
         wait(0.06);
        } 
}
int main() {
        char    data[10];
    data[0]   = 'd';
    data[1]   = 'a';
    data[2]   = 'v';
    data[3]   = 'i';
    data[4]   = 'd';
    data[5]   = '\0';
    while (1) {
        sent(data);
        wait(1);

       /* i2c.write(addr8bit, data, 1 );
        interrupt = 1; 
         wait(0.00001);
        interrupt = 0; 
        data[0]='r';
*/
    }
    }