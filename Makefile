# elementOS Build Script
# This builds elementOS, and does other things too. Try make commands.
# Based on the Makefile of Kevin Lange (https://github.com/klange)
#=================================================================
#Setup

CC := clang
CFLAGS := -c -ffreestanding -fno-builtin  -nostdlib -nostdinc -fno-stack-protector -target i586-pc-linux-gnu
AS := nasm -f elf
ASM := nasm
AFLAGS := -f elf

LD := ./tool/binutils/bin/i586-elf-ld
LFLAGS := -m elf_i386

#FILES
KERNELFILES := $(patsubst %.c,%.o,$(wildcard kernel/*.c)) $(patsubst %.s,%.o,$(wildcard kernel/arch/*.s))

#Rules
.PHONY: all clean

all: system
aux: docs
system: kernel

install: system
	@echo "[Install] Install not implemented"

kernel: kernel/boot.o ${KERNELFILES}
	@echo "Building Kernel..."
	@${LD} ${LFLAGS} -T kernel/link.ld -o kernel.elf ${KERNELFILES}
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
kernel/boot.o: kernel/arch/x86-boot.s
	@${AS} -o kernel/boot.o kernel/arch/x86-boot.s

clean:
	rm -R -f ./kernel/*.o
	rm -R -f ./kernel/arch/*.o
	rm -f kernel.elf