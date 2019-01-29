/*
 * bluetooth_uart.c
 *
 * Created: 2019-01-25 PM 4:54:21
 * Author: ryo
 * Module: Bluetooth Module HC-06(https://www.olimex.com/Products/Components/RF/BLUETOOTH-SERIAL-HC-06/resources/hc06.pdf)
 */

#include <mega128.h>
#include <stdint.h>
#include <stdio.h>
#include <delay.h>

#define _ALTERNATE_PUTCHAR_
void putchar(char c){while(!(UCSR0A&(1<<UDRE0)));UDR0=c;}

#define BAUD 38400UL                            // Unsigned Long
#define F_CPU 16000000UL 
void uart0_init(void)
{
    uint16_t UBRR_VALUE = (F_CPU / (BAUD * 16UL)) - 1;
    
    UCSR0A = 0x00;                              // Initialize 
    UCSR0B = 0x00;                              // Disable while setting baud rate
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);     // Asynchronous
                                                // Parity:          Disabled
                                                // Character Size:  8 bit
                                                // Stop Bit:        1 bit
    UBRR0H = (uint8_t)(UBRR_VALUE >> 8);        
    UBRR0L = (uint8_t)(UBRR_VALUE);
    UCSR0B = (1 << TXEN0) | (1 << RXEN0);       // Enable UART Tx
}

void main(void)
{
    DDRG = 0x03;                                // LED Test Code
    PORTG = 0x01;
    
    uart0_init();
    
    while (1)
    {
        PORTG ^= 0x03;
        delay_ms(200);
    }
}
