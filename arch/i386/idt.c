/*
 * idt.c
 * (c) 2019 Zachary James Schlotman
 * This sets up interupts
 */
#include "idt.h"
#include "mem.h"
#include "lib.h"
//Semi-Hardcoded way to handle exceptions
void ehandle(){
asm("a:");	panic("00");
asm("b:");	panic("01");
	panic("02");
	panic("03");
	panic("04");
	panic("05");
	panic("06");
	panic("07");
	panic("08");
	panic("09");
	panic("0a");
	panic("0b");
	panic("0c");
	panic("0d");
//	panic("0e");
	return;
	panic("0f");
	panic("10");
	panic("11");
	panic("12");
	panic("13");
	panic("14");
	panic("15");
	panic("16");
	panic("17");
	panic("18");
	panic("19");
	panic("1a");
	panic("1b");
	panic("1c");
	panic("1d");
	panic("1e");
	panic("1f");
}
//puts the basic idt stuff together
void idt(){
	struct IDTDescr *idt = (struct IDTDescr *)malloc(sizeof(*idt)*256);
	bzero(idt,sizeof(*idt)*256);
	idt[0x80].offset_1 = (uint16_t)(0x15000  & 0xffff) ;
	idt[0x80].offset_2 = (uint16_t)(0x15000 >> 16);
	idt[0x80].selector = 0x8;
	idt[0x80].type_attr = 0b10001110;
	uint8_t inssize;
	asm("movb $(b-a),%0" : "=m"(inssize));
	uint32_t paddr = (uint32_t)ehandle;
	for(int i = 0 ; i < 0x20;i++){
		idt[i].offset_1 = (uint16_t)(paddr + 9 + inssize*i ) & 0xffff;
		idt[i].offset_2 = (uint16_t)((paddr + 9 + inssize*i) >> 16);
		idt[i].selector = 0x8;
		idt[i].type_attr = 0b10001110;
	}
	struct idt_info inf;
	inf.size = sizeof(*idt)*256-1;
	inf.pntr = idt;
	asm("lidt %0" : :"m"(inf));
}

void irq(){
	struct IDTDescr *irq = (struct IDTDescr *)malloc(sizeof(*idt)*256);
}
