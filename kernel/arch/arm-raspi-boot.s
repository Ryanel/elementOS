;
; boot.s
; The entry point of the kernel
; By (as in edited by) Corwin Mcknight
;
;To keep this in the first portion of the binary.
section ".text.boot"
global start 
start:
  ; Setup the stack.
  mov sp, 0x8000
 
  ; Clear out bss.
  ldr r4, = bss_start
  ldr r9, = bss_end
  mov r5, 0
  mov r6, 0
  mov r7, 0
  mov r8, 0
  ;b 2 ;What?
 
1:
  ;store multiple at r4.
  stmia r4!, {r5-r8}
 
  ; If we are still below bss_end, loop.
2:
  cmp r4, r9
  blo 1b
 
  ; Call kernel_main
  ldr r3, arm_main
  blx r3
 
  ; halt
halt:
  wfe
  b halt