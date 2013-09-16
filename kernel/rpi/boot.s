
.equ SCREEN_HEIGHT, 768
.equ SCREEN_WIDTH, 1360
.equ COLOR_DEPTH, 16

_start:
	mov r0,#SCREEN_WIDTH /* was 1024 */
	mov r1,#SCREEN_HEIGHT
	mov r2,#COLOR_DEPTH
	bl InitialiseFrameBuffer
	fbInfoAddr .req r4
	mov fbInfoAddr,r0
	bl SetGraphicsAddress
	ldr r0, =format
	mov r1, #11
	ldr r2, =buffer
	ldr r3,[fbInfoAddr]
	bl FormatString
	b main

.section .data
format:
.rept 20
	.ascii "---------|"
.endr
formatEnd:
buffer:
	.space 256