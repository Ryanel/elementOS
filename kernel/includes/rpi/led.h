#ifndef RPI_LED_H
#define RPI_LED_H

void led_init(void);
void led_invert(void);
void output32(unsigned int num);
void output(unsigned int num);
void output_n(unsigned int num, unsigned int count);
#endif	/* LED_H */