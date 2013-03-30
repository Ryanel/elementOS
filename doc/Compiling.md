Compiling
========================================

All
----------------------------------------

Command Line
----------------------------------------
# Types

## C
>    clang -c -ffreestanding --fno-builtin -arch $ARCH -march $ARCHSUB [FILE] -o $BUILD/[FILE].o
> (if using project toolchain, use $TOOLS/clang instead of clang)