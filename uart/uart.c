/*
 * uart.c
 *
 * Created: 2019-01-10 PM 1:55:49
 * Author: ryo
 */
#include <mega128.h>
#include <stdio.h>
#include <delay.h>

//#define _ALTERNATE_PUTCHAR_
//void putchar(char c)
//{
//    while(!(UCSR0A&(1<<UDRE0)));
//    UDR0 = c;
//}

// UART0 initialize
// desired baud rate: 9600
// actual: baud rate:9600 (0.0%)
// char size: 8 bit
// parity: Disabled

void uart0_init()
{
    UCSR0B = 0x00; //disable while setting baud rate
    UCSR0A = 0x00;
    UCSR0C = 0x0E;
    UBRR0H = 0x00; //set baud rate hi
    UBRR0L = 0x67; //set baud rate lo
    UCSR0B = (1<<TXEN0);
}

void TX0_ch(unsigned char data)
{
    while(!(UCSR0A&(1<<UDRE0)));
    UDR0 = data;
}


void main(void){  
    PORTG = 0x01;
    DDRG = 0x03;  
    uart0_init();
     
    while(1){
        TX0_ch('1');
        //delay_ms(100);
        //printf("ABC");
        //printf("ABC");
        PORTG ^= 0x03;
        delay_ms(PORTG * 1000);
    }
}
