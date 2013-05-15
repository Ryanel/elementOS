rm -R -f ./kernel/*.o
rm -R -f ./kernel/arch/*.o
rm -R -f ./kernel/video/*.o
rm -f kernel.elf
nasm -f elf -o boot.o kernel/arch/x86-boot.s
clang -c  -ffreestanding -fno-builtin  -nostdlib -nostdinc -fno-stack-protector  -ccc-host-triple i586-elf-linux-gnu -I./kernel/includes -o main.o kernel/main.c
clang -c -ffreestanding -fno-builtin  -nostdlib -nostdinc -fno-stack-protector -ccc-host-triple i586-elf-linux-gnu  -I./kernel/includes -o low.o kernel/low.c
clang -c -ffreestanding -fno-builtin  -nostdlib -nostdinc -fno-stack-protector -ccc-host-triple i586-elf-linux-gnu -I./kernel/includes -o error.o kernel/error.c
clang -c -ffreestanding -fno-builtin  -nostdlib -nostdinc -fno-stack-protector -ccc-host-triple i586-elf-linux-gnu -I./kernel/includes -o textmode.o kernel/video/textmode.c
./tool/binutils/bin/i586-elf-ld -T kernel/x86-link.ld -o kernel.elf *.o