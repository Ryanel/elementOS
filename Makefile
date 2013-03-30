# elementOS Build Script
# This builds elementOS, and does other things too. Try make commands.
# Based on the Makefile of Kevin Lange (https://github.com/klange)
#=================================================================
#Setup

CC := clang
CFLAGS := -c -ffreestanding --fno-builtin -target i386-elf

ASM := nasm
AFLAGS := -f elf

LD := ld
LFLAGS :=

#FILES


#Rules
.PHONY: all clean

all: system
aux: docs
system: kernel

install: system
	@echo "[Install] Install not implemented"

kernel:  kernel/arch/x86-boot.o
	@echo "Building Kernel..."
commands:
	@echo "Avalable commands (prefixed by make):"
	@echo "-------------------------------------"
	@echo "all      | Makes Everything"
	@echo "run      | Runs OS in a emulator"
	@echo "system   | Builds the core system"
	@echo "install  | Makes the base filesystem"
	@echo "         | but does not install it to"
	@echo "         | a media."
	@echo "mkmedia-*| Creates a bootable system "
	@echo "         | image of the selected type"

%.o: %.c
	@${CC} ${CFLAGS} -I./kernel/includes -o $@ $<
kernel/arch/x86-boot.o: kernel/arch/x86-boot.s
	${ASM} ${AFLAGS} -o kernel/arch/x86-boot.o kernel/arch/x86-boot.s

clean:
	rm -R *.o