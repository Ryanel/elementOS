//pit.c
#include <stdio.h>
#include <arch/x86.h>
void pit_phase(int hz)
{
    int divisor = 1193180 / hz;       /* Calculate our divisor */
    outb(0x43, 0x36);             /* Set our command byte 0x36 */
    outb(0x40, divisor & 0xFF);   /* Set low byte of divisor */
    outb(0x40, divisor >> 8);     /* Set high byte of divisor */
}
int timer_ticks = 0;
int timer_ticks_old = 0;

/* Handles the timer. In this case, it's very simple: We
*  increment the 'timer_ticks' variable every time the
*  timer fires. By default, the timer fires 18.222 times
*  per second. Why 18.222Hz? Some engineer at IBM must've
*  been smoking something funky */
int tpds=0; //timer pip dynamic state
void timer_handler(struct regs *r)
{
    /* Increment our 'tick count' */
    timer_ticks++;
    //printf("One second has passed\n");
    volatile unsigned char *videoram = (unsigned char *)0xB8000;
    switch(tpds)
    {
    	case 0:
    		videoram[158]='|';
    		tpds++;
    		break;
    	case 9:
    		videoram[158]='/';
    		tpds++;
    		break;
    	case 18:
    		videoram[158]='-';
    		tpds++;
    		break;
    	case 27:
    		videoram[158]='\\'; //Just : "\"
    		tpds++;
    		break;
    	case 36:
    		videoram[158]='|';
    		tpds=0;
    		break;
    	default:
    		tpds++;
    		break;
    }
}

/* Sets up the system clock by installing the timer handler
*  into IRQ0 */
void pit_install()
{
    /* Installs 'timer_handler' to IRQ0 */
    irq_install_handler(0, timer_handler);
}

int pit_has_ticked() //If no ticks, returns 0, else it returns how many ticks have happened since the last call;
{
	int retval=timer_ticks-timer_ticks_old;
	timer_ticks_old=timer_ticks;
	return retval;

}

void pit_wait(int ticks)
{
    unsigned int eticks;

    eticks = timer_ticks + ticks;
    while(timer_ticks < eticks)
    {
    	
    }
}