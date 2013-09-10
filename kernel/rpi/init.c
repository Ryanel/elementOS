#include <types.h>
#include <rpi/uart.h>
#define UNUSED(x) (void)(x)

// kernel main function, it all begins here


const char greeter[] = "\r\nelementOS v. 0.0.0.2 (git) (arm:rpi)\r\n";
volatile unsigned int* const UART0 = (unsigned int*)0x20201000;
static void uart_print(const char *s)
{
	while(*s != '\0') {
	*UART0 = (unsigned int)(*s); /* send to UART */
		s++;
	}
}

void kernel_main(uint32_t r0, uint32_t r1, uint32_t atags) {
    UNUSED(r0);
    UNUSED(r1);
    UNUSED(atags);
	uart_init();
	int i=0;
	uart_print("Hello");
	for(i = 0; i < 10000000; ++i) { }
    while(true)
    {
    }
}