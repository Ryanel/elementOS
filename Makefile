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
KERNELFILES := $(patsubst %.c,%.o,$(wildcard kernel/*.c)) $(patsubst %.c,%.o,$(wildcard kernel/video/*.c)) $(patsubst %.s,%.o,$(wildcard kernel/arch/*.s))
#Rules
.PHONY: all clean

all: system install mkmedia run
aux: docs
system: kernel

install:
	@echo -e "\e[1;34mInstalling kernel into filesystem...\e[1;37m"
	@cp ./kernel.elf fs/kernel.elf

kernel: clean kernel/boot.o ${KERNELFILES}
	@echo -e "\e[1;34mBuilding Kernel...\e[1;37m"
	@${LD} ${LFLAGS} -T kernel/link.ld -o kernel.elf ${KERNELFILES}
commands:
	@echo -e "\e[1;34mAvalable commands (prefixed by make):\e[1;37m"
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
	@echo -e "\e[1;34mCleaning junk...\e[1;37m"
	@rm -R -f ./kernel/*.o
	@rm -R -f ./kernel/arch/*.o
	@rm -R -f ./kernel/video/*.o
	@rm -f kernel.elf

mkmedia: mkmedia-iso
mkmedia-iso:
	@echo -e "\e[1;34mCreating ISO...\e[1;37m"
	@genisoimage -R -b boot/grub/stage2_eltorito -input-charset utf-8 -quiet -no-emul-boot -boot-load-size 4 -boot-info-table -o bootable.iso fs
run:
	@echo -e "\e[00;31mUndefined emulator!\e[1;37m"