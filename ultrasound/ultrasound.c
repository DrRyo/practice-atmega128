/*
 * ultrasound.c
 *
 * Created: 2019-01-22 AM 11:17:55
 * Author: ryo
 * 
 * Sensor: HC-SR04 (https://www.mpja.com/download/hc-sr04_ultrasonic_module_user_guidejohn.pdf)
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
    UCSR0B = (1 << TXEN0);                      // Enable UART Tx
}

#define SONAR_CM 58
volatile unsigned int pulse_count = 0;
volatile unsigned int toggle = 0;
void sonar_init(void)
{
    EIMSK = (1 << INT0);                        // INT0 External Interrupt Enable
    EICRA = ((1 << ISC01) | (1 << ISC00));      // INT0 Rising Edge Interrupt Request
    SREG = 0x80;                                // Global Interrupt Enable
}

interrupt [TIM0_OVF] void count_pulse(void)
{
    pulse_count++;                              // Increase at every 58us
}

interrupt [EXT_INT0] void read_pulse(void)
{
    uint16_t TCNT_VALUE;
    
    if(toggle == 0){
        //At Rising Edge
        pulse_count = 0;
        TIMSK = (1 << TOIE0);                   // Time Counter 0 Enable (8-bit Timer/Counter)
        TCCR0 = (1 << CS01);                    // Set prescaling 8
                                
        TCNT_VALUE = (1 / F_CPU) * 8 * SONAR_CM;// 1 / 16 * 10^6 = 0.0000000625s
                                                // 0.0000000625s * 8 = 0.5us
                                                // 0.000058 / 0.0000005 = 116
                                                
        TCNT0 = 255 - TCNT_VALUE + 1;           // 8bit: 255, (255 - TCNT_VALUE + 1) = 140
                  
        EICRA = (1 << ISC01);                   // INT0 Falling Edge Interrupt Request 
        toggle = 1;
    }else{
        //At Falling Edge
        printf("Object is %d cm far from sensor.\r\n", pulse_count);
         
        EICRA = ((1 << ISC01) | (1 << ISC00));  // INT0 Rising Edge Interrupt Request
        toggle = 0;
    }
}


void main(void)
{
    DDRG = 0x03;                                // LED Test Code
    PORTG = 0x01;
    
    DDRD = 0x02;                                // Use PortD1 as output
    PORTD = 0x00;
    
    uart0_init();
    sonar_init();
    
    while (1)
    {
        PORTG ^= 0x03;
        
        PORTD = 0x02;
        delay_us(10);
        PORTD = 0x00;
        
        delay_ms(200);
    }
}
