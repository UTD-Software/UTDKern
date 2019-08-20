#include <stdio.h>
void readSector(char *buf,uint32_t lba){
	asm("pushal");
	asm("mov $0xc,%ah");
	asm("mov %0,%%ebx" : : "m"(buf));
	asm("mov %0,%%ecx" : : "m"(lba));
	asm("int $0x80");
	asm("popal");
}
