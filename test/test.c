/*
 * test.c
 *
 * Created: 2019-01-07 PM 2:36:10
 * Author: ryo
 */

#include <mega128.h>
#include <delay.h>
#include <stdio.h>

void main(void)
{
    //unsigned int i = 2, n = 3;
    //DDRG = 0;    
    while (1)
    {
        //printf("%d, %d", DDG2, DDG3);
        if(PING & 0x04){
            if(PING & 0x08){
                PORTG = 0x00;
            }else{
                PORTG = 0x02;
            }
        }else{
            if(PING & 0x08){
                PORTG = 0x01;
            }else{
                PORTG = 0x03;
            }
        }
        delay_ms(200);
    /*
        PORTG = 0x03;
        delay_ms(200);
        PORTG = 0x00;
        delay_ms(200);
    */
    }
}
