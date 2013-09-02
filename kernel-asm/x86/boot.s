;
; boot.s
; The entry point of the kernel
; By (as in edited by) Corwin Mcknight -- Credit to James Molloy (jamesmolloy.co.uk)
;

MBOOT_PAGE_ALIGN    equ 1<<0
MBOOT_MEM_INFO      equ 1<<1
MBOOT_HEADER_MAGIC  equ 0x1BADB002
MBOOT_HEADER_FLAGS  equ MBOOT_PAGE_ALIGN | MBOOT_MEM_INFO
MBOOT_CHECKSUM      equ -(MBOOT_HEADER_MAGIC + MBOOT_HEADER_FLAGS)

[BITS 32]

[GLOBAL mboot]
[EXTERN code]
[EXTERN bss]
[EXTERN end]
section .__mbHeader
align 0x4
mboot:
	dd  MBOOT_HEADER_MAGIC
	dd  MBOOT_HEADER_FLAGS
	dd  MBOOT_CHECKSUM

	dd  mboot
	dd  code
	dd  bss
	dd  end
	dd  start

section .text

dochar:
	call cprint
printstring:
	mov eax, [esi]
	lea esi, [esi+1]
	cmp al, 0
	jne dochar
	add byte [ypos], 1
	mov byte [xpos], 0
	ret

cprint:
	mov ah, 0x0F ;Color
	mov ecx, eax
	movzx eax, byte [ypos]
	mov edx, 160
	mul edx
	movzx ebx, byte [xpos]
	shl ebx, 1

	mov edi, 0xb8000
	add edi, eax
	add edi, ebx

	mov eax, ecx
	mov word [ds:edi], ax
	add byte[xpos], 1
	ret

[GLOBAL start]
start:
	cli
	mov esi, startingmsg
	call printstring

	mov esi, asmtext
	call printstring

halt:
	hlt
	jmp halt
startingmsg: db "elementOS (asm) started", 0
asmtext: db "Assembly text working!", 0
xpos db 0
ypos db 0
