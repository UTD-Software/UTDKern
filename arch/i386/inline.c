#include "lib.h"
//Some inline shit
uint16_t inw(uint16_t port){
	uint16_t ret;
	asm ("inw %1 ,%0" : "=a"(ret) : "Nd"(port));
	return ret;
}
uint8_t inb(uint16_t port)
{
    uint8_t ret;
    asm volatile ( "inb %1, %0"
                   : "=a"(ret)
                   : "Nd"(port) );
    return ret;
}
void outb(uint16_t port,uint8_t v)
{
    asm volatile ( "outb %0, %1" : : "a"(v), "Nd"(port) );
}
void outw(uint16_t port,uint16_t v){
    asm volatile ( "outw %0, %1" : : "a"(v), "Nd"(port) );
}
