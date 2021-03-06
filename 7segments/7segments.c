/*
 * 7segments.c
 *
 * Created: 2019-01-09 PM 2:55:49
 * Author: ryo
 */

#include <mega128.h>
#include <delay.h>

void main(void)
{
    PORTG = 0x01;
    DDRG = 0x03;
    DDRC = 0xff;
    while (1) {
        PORTG ^= 0x03;
        // PORTC = 0;
        
        PORTC = 0xff ^ 0x01;
        delay_ms(1000);
        PORTC = 0xff ^ 0x02;
        delay_ms(1000);
        PORTC = 0xff ^ 0x04;
        delay_ms(1000);
        PORTC = 0xff ^ 0x08;
        delay_ms(1000);
        PORTC = 0xff ^ 0x10;
        delay_ms(1000);
        PORTC = 0xff ^ 0x20;
        delay_ms(1000);
        PORTC = 0xff ^ 0x40;
        delay_ms(1000);
        PORTC = 0xff ^ 0x80;
        delay_ms(1000);
        
        /*
        PORTC = 0xff ^ 0x06; 
        delay_ms(500);
        PORTC = 0xff ^ 0x5B; 
        delay_ms(500);
        PORTC = 0xff ^ 0x4F; 
        delay_ms(500);
        PORTC = 0xff ^ 0x66;
        delay_ms(500);
        PORTC = 0xff ^ 0x6D;
        delay_ms(500);
        PORTC = 0xff ^ 0x7D;
        delay_ms(500);
        PORTC = 0xff ^ 0x07;
        delay_ms(500);
        PORTC = 0xff ^ 0x7F;
        delay_ms(500);
        PORTC = 0xff ^ 0x6F; 
        delay_ms(500);
        */
    }
    return;
}
