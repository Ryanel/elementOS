elementOS
========
elementOS is a OS. It currently does absolutely nothing. But fun. It does that.

Features
========
Booting
--------
A standard feature, the booting of the OS uses GRUB, and can actually boot. This is more than some OS's can do, so I'm proud! :)

Logging
--------
It has a log function that makes things pretty. How is pretty not a feature?

GDT
--------
It can initialise the GDT, so thats something.

80x24 Textmode
--------
Going back to those old computing days, the screen is in true 80x24 text mode (Not 80x25, as one is reserved for the title bar. Can print text and numbers, how amazing! /endsarcasm{now}

Title Bar
--------
The bar that is on top of the screen is the title bar. It shows status information such as the clock, the program name, status indicators, and the halt icon. It currently does none of this, except for the "elementOS" in the center.

Error Handeling
--------
There are 4 diffrent kinds of errors - a panic, an oops, a woah, and a halt. A panic is when something isn't recoverable from, but an oops is, and can be 'rewound'. A woah is when something unexpected happends, it is really just a status message. A halt is a litteral: "SYSTEM FAILURE! BOOOOOOOOOOOOM!" minus the explosion. The system litterally just stops EVERYTHING, and then sits idle. This is when something REALLY wrong happens (the system overwrites a memory mapped device). A halt can always be triggered by a CTRL+SHIFT+ALT+F12, in which the system will soft-halt (the keyboard led's will blink).

Building
========
See Building.md in docs/

Branches / Reales
========

Master / stable (Always working)
--------
Stable code for all Architectures. Contains litterally everything. Updated every stable release.

x86 / unstable (Not working)
--------
Latest x86 specific code. Look here for the latest features on x86. Might not be stable. Updated anytime.

raspberry-pi / untested (Not working)
--------
Latest raspberry-pi / ARM specific code. Look here for the latest features on raspberry pi. Might not be stable. Updated anytime. 
