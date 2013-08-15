elementOS
========
elementOS is a OS. It currently does absolutely nothing. But fun. It does that.

Kernel
--------
The kernel, ununtrium or 113, is your run of the mill macrokernel for now. It will be a highfunctioning hybrid/micro kernel.

Building
--------
You need to have nasm gcc clang make flex bison libgmp3-dev libmpfr-dev libmpc-dev libmpc-dev genisoimage doxygen installed in order to compile. ( On debian based systems sudo apt-get install nasm qemu gcc make flex bison libgmp3-dev libmpfr-dev libmpc-dev libmpc-dev genisoimage doxygen ). 
You then cd into ./tool and run chmod +x ./makebinutils.sh && ./makebinutils.sh .
This builds the cross compiler. Then simply go to the root project folder and build the os with make .
Then, just simply type make run to launch qemu.

Ports / Status
========

x86
--------
Latest x86 specific code. Look here for the latest features on x86. Might not be stable. Will always be able to compile, but it might not work / be very buggy. Updated anytime.

raspberry-pi / untested (Not working)
--------
Latest raspberry-pi / ARM specific code. Look here for the latest features on raspberry pi. Might not be stable (compile or boot). Updated anytime. Yet to be started after first crash.

chip-8
--------
Possible port of elementOS-asm to SuperCHIP8. It seems like a fun chalenge.
