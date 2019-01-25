n/*
 * infra_red.c
 *
 * Created: 2019-01-15 PM 5:39:25
 * Author: ryo
 * Sensor: SHARP GP2Y0A21YK0F (http://www.sharp-world.com/products/device/lineup/data/pdf/datasheet/gp2y0a21yk_e.pdf)
 */

#include <mega128.h>
#include <stdint.h>
#include <stdio.h>
#include <delay.h>

#define _ALTERNATE_PUTCHAR_
void putchar(char c){while (!(UCSR0A & (1<<UDRE0)));UDR0=c;}

// UART0 initialize
// desired baud rate: 9600
// actual baud rate: 9600 (0.0%)
// char size: 8 bit
// parity: Disabled
void uart0_init(void)
{
    UCSR0B = 0x00; //disable while setting baud rate
    UCSR0A = 0x00;
    UCSR0C = 0x06; //0x0E;
    UBRR0H = 0x00; //set baud rate hi
    UBRR0L = 0x67; //set baud rate lo
    UCSR0B = 0x18;
}

void adc_interrupt_init(void)
{
    // https://webnautes.tistory.com/991
    // http://maxpulse.tistory.com/153
    // http://www.newtc.co.kr/dpshop/bbs/board.php?bo_table=m41&wr_id=772&sca=&sfl=wr_subject%7C%7Cwr_content&stx=adc&sop=and
    
    DDRF = 0x00;
    ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // Set ADC prescalar to 128 - 125KHz sample rate @ 16MHz
    ADMUX |= (1 << REFS0);  // Set ADC reference to AVCC
    ADCSRA |= (1 << ADEN);  // Enable ADC
    ADCSRA |= (1 << ADSC);  // Start A2D Conversions
}

uint16_t read_adc(void)
{
    ADMUX &= 0xE0;          // Single Ended Input with ADC0
    ADMUX |= 0x00;          // No mean          
     
    
    ADCSRA |= (1 << ADSC);  // Start A2D Conversions
    while ((ADCSRA & (1 << ADSC)));
    ADCSRA |= (1 << ADIF);
    
    return ADCW; 
}

void main(void)
{
    uint16_t ir_value;
    //char val[10];
    
    PORTG = 0x01;
    DDRG = 0x03;
    
    uart0_init();
    adc_interrupt_init();
    
    while (1)
    {
        PORTG ^= 0x03;
        ir_value = read_adc();
        
        //printf("ABC");
        //sprintf(val, "%u", ir_value);
        printf("Sensor Value : %u\r\n", ir_value);         
        delay_ms(80000 / ir_value + 100);
    }
}
