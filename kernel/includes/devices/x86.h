#ifndef X86_DEVICES_HEADER
#define X86_DEVICES_HEADER
//PIT
void pit_wait(int ticks);
void pit_install();
void pit_phase(int hz);
int pit_has_ticked();
#endif