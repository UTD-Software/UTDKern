#include <stdio.h>
struct Entry *_opendir(const char *dir){
	asm("pushal");
	asm("mov %0,%%ebx" : : "m"(dir));
	asm("mov $0xb,%ah");
	asm("int $0x80");
	struct Entry *ret;
	asm("mov %%eax,%0" :"=m"(ret));
	asm("popal");
	return ret;
}
