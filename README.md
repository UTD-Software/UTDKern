[Critter System]<br>
Critter aims to be a fully function operating system with multiformat support. So far this project has been created alone by myself. I am going to need other people to help me on this<br>
so I will be documenting my code. I do not know what hardware this will run on I only use qemu to run this software. If you have a i80386 it might be fine but any other slightly different architecture and you'll have problems with it. The kernel is going through a lot of changes right now and I may be opening up the work to other people soon. I am likely going to refactor most of the code and functioning of the bootloader and some of the kernel. <br>
What I have working:<br>
low level file system<br>
a broken shell<br>
an init stub<br>
a very rigid bootloader that deals with a.out and elf formats(I plan to majorly refactor this in the near future. It does what I need but if I want other people to use it there need to be more options for what kind of system it boots into, what modules to load, etc.)<br>
ATA PIO mode(need to change this before multitasking currently polls instead of waiting for an IRQ probably an easy fix but I don't know the specifics)<br>
Paging works but the problem is I don't even know what memory my kernel uses, I know where it's loaded but I have a bad habbit of writing stuff to random memory addresses. The fix for this is in kernel.c and kernel.h for providing a better way for the kernel to store critical information<br>
My goals for 2019 are:<br>
Paging working with a fully working userland shell<br>
Simple kernel modules<br>
Early Support for multiprocessing <br>
Several kernel arguments including adding an option for a graphical environment<br>
My goals for 2020-2023:<br>
better support for ATA SATA and AHCI<br>
An implentation of a POSIX compliant C Library. Whether I port newlib or write my own is still undescied. Currently I have a very minimalistic userland C library that can handle basic I/O with files and the keyboard a few memory functions<br>
An initramfs<br>
An actually decent bootloader running in a vesa vga environment at 800x600 resolution<br>
Multithreading and full multiprocessing<br>
A vesa driver that supports higher resolutions for the kernel and userland<br>
Dynamic Linking.<br>
Networking?<br>
FILE FORMATS SUPPORTED BY BOOTLOADER<br>
RAW,A.OUT(for a later stage bootloader),CRITTER ELF32<br>

FILE FORMATS SUPPORTED BY KERNELRAW(technically supported but depreciated),CRITTER ELF32<br>
FILE FORMATS I WISH TO ADD IN THE NEAR FUTURE<br>
CRITTER PE32<br>
FILE FORMATS I WISH TO ADD IN THE LONG RUN<br>
MACH-O<br>
Support for running programs from other operating systems. I have an idea on how to do that with a dynamic idt and reverse engineering NT and XNU kernels linux should work as sonn as I get dynamic linking to work.  but im still working on the theory. Ask me about it.

