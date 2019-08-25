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
void io_wait(){
	for(int i = 0; i < 4096;i++)
		i++;
}
void remap(){
	unsigned char a1,a2 ;
	a1 = inb(PIC1_DATA);
	a2 = inb(PIC2_DATA);
	outb(PIC1_COMMAND,ICW1_INIT|ICW1_ICW4);
	io_wait();
	outb(PIC2_COMMAND,ICW1_INIT|ICW1_ICW4);
	io_wait();
	outb(PIC1_DATA,0x20);
	io_wait();
	outb(PIC2_DATA,0x28);
	io_wait();
	outb(PIC1_DATA,4);
	io_wait();
	outb(PIC2_DATA,2);
	io_wait();
	outb(PIC1_DATA,ICW4_8086);
	io_wait();
	outb(PIC2_DATA,ICW4_8086);
	io_wait();
	outb(PIC1_DATA,a1);
	outb(PIC2_DATA,a2);
}

void clear_masks(){
	for(int i = 0; i < 8;i++)
		outb(PIC1_DATA,inb(PIC1_DATA) & ~(1 << i));
	for(int i = 0; i < 8;i++)
		outb(PIC2_DATA,inb(PIC2_DATA) & ~(1 << i));
}
#define PIC_EOI		0x20		/* End-of-interrupt command code */
 
void eoi(unsigned char irq)
{
		if(irq >= 8)
					outb(PIC2_COMMAND,PIC_EOI);
		 
			outb(PIC1_COMMAND,PIC_EOI);
}
void irqn(){
	puts("This interrupt  is not implemented\n");
}//puts the basic idt stuff together
void idt(){
	remap();
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
	for(int i = 0x20; i < 0x2f;i++){
		idt[i].offset_1 = ((uint16_t)irqn);
		idt[i].offset_2 = ((uint16_t)irqn >> 16);
		idt[i].selector = idt[0x80].selector;
		idt[i].type_attr = idt[0x80].type_attr;
	}
	idt[0x2f].offset_1 = (uint16_t)((uint32_t)IRQ1 & 0xffff);
	idt[0x2f].offset_2 = (uint16_t)((uint32_t)IRQ1 >> 16);
	idt[0x2f].selector = 0x8;
	idt[0x2f].type_attr = 0b10001110;
	idt[0x2e].offset_1 = (uint16_t)((uint32_t)IRQ0 & 0xffff);
	idt[0x2e].offset_2 = (uint16_t)((uint32_t)IRQ0 >> 16);
	idt[0x2e].selector = idt[0x2F].selector;
	idt[0x2e].type_attr = 0b10001110;
	struct idt_info inf;
	inf.size = sizeof(*idt)*256-1;
	inf.pntr = idt;
	asm("lidt %0" : :"m"(inf));
}

void irq(){
	struct IDTDescr *irq = (struct IDTDescr *)malloc(sizeof(*idt)*256);
}
