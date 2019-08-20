#include <stdio.h>
int open(const char *path,int flags){
	asm("pushal");
	asm("mov $0xd,%ah");
	asm("mov %0,%%ebx" : : "m"(path));
	asm("mov %0,%%ecx" : : "m"(flags));
	asm("int $0x80");
	int ret;
	asm("mov %%eax,%0" : "=m"(ret));
	asm("popal");
	return ret;
}
