#include <mega128.h>
#include <delay.h>

void main(void)
{
    PORTG = 0x01;
    DDRG = 0x03;
    while (1)
    {
        PORTG ^= 0x03;
        delay_ms(2000);
    }
}
