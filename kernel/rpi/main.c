#include <rpi/memory.h>

void uart_putc ( unsigned int c )
{
    while(1)
    {
        if((GET32(UART0_FR)&0x20)==0) break;
    }
    PUT32(UART0_DR,c);
}
void uart_puts(const char *str) {
    while (*str) {
        uart_putc(*str++);
    }
}
//------------------------------------------------------------------------
unsigned int uart_getc ( void )
{
    while(1)
    {
        if((GET32(UART0_FR)&0x10)==0) break;
    }
    return(GET32(UART0_DR));
}
//------------------------------------------------------------------------
void uart_init ( void )
{
    unsigned int ra;

    PUT32(UART0_CR,0);

    ra=GET32(GPFSEL1);
    ra&=~(7<<12); //gpio14
    ra|=4<<12;    //alt0
    ra&=~(7<<15); //gpio15
    ra|=4<<15;    //alt0
    PUT32(GPFSEL1,ra);

    PUT32(GPPUD,0);
    for(ra=0;ra<150;ra++) dummy(ra);
    PUT32(GPPUDCLK0,(1<<14)|(1<<15));
    for(ra=0;ra<150;ra++) dummy(ra);
    PUT32(GPPUDCLK0,0);

    PUT32(UART0_ICR,0x7FF);
    PUT32(UART0_IBRD,1);
    PUT32(UART0_FBRD,40);
    PUT32(UART0_LCRH,0x70);
    PUT32(UART0_CR,0x301);
}

int main( unsigned int earlypc )
{
	DrawCharacter('e', 5, 5);
}
