#ifndef X86_HEADER
#define X86_HEADER
///Initialises the GDT
int gdt_install();
///Initialises the IDT
int idt_install();
///Initialises and loads the ISR's
int isrs_install();
///Initialises the IRQ's
int irq_install();
///Sets up the keyboard
void kb_install();
void setupPaging();
///Datatype to represent all x86 regesters
struct regs
{
	unsigned int gs, fs, es, ds;      /* pushed the segs last */
	unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax;  /* pushed by 'pusha' */
	unsigned int int_no, err_code;    /* our 'push byte #' and ecodes do this */
	unsigned int eip, cs, eflags, useresp, ss;   /* pushed by the processor automatically */ 
};
typedef struct regs registers_t;
/// Installs an IRQ
void irq_install_handler(int irq, void (*handler)(struct regs *r));
/// Internal
void idt_set_gate(unsigned char num, unsigned long base, unsigned short sel, unsigned char flags);
#endif
