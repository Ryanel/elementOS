#ifndef X86_HEADER
#define X86_HEADER
int gdt_install();
int idt_install();
int isrs_install();
int irq_install();
void kb_install();
void setupPaging();
struct regs
{
	unsigned int gs, fs, es, ds;      /* pushed the segs last */
	unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax;  /* pushed by 'pusha' */
	unsigned int int_no, err_code;    /* our 'push byte #' and ecodes do this */
	unsigned int eip, cs, eflags, useresp, ss;   /* pushed by the processor automatically */ 
};

void irq_install_handler(int irq, void (*handler)(struct regs *r));
#endif