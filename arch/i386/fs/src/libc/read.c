#include <stdio.h>
int read(int fd,void *buf,unsigned int n){
	asm("pushal");
	asm("mov $0x3,%ah");
	asm("mov %0,%%ebx" : :"m"(fd));
	asm("mov %0,%%ecx" : :"m"(buf));
	asm("mov %0,%%edx" : :"m"(n));
	asm("int $0x80");
	int a;
	asm("mov %%eax,%0" : "=m"(a));
	asm("popal");
	return a;
}
