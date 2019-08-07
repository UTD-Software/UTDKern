#include "lib.h"
#include <stdint.h>
#include "mem.h"
uint32_t paged[1024] __attribute__((aligned(4096)));

void ldpgd(uint32_t *p);
/*
 *Initializing paging
 */
int init_page(){
	for(int i = 0; i < 1024;i++){
		paged[i] = 1;
	}
	int addr = 0;

	uint32_t paget[1024] __attribute__((aligned(4096)));
	for(int i = 0; i < 1024;i++,addr+=4096){
		paget[i] = addr | 0b11;
	}
	paged[0] = 0b11 | (uint32_t)paget;
	addr = 0x01000000;
	for(int i = 1; i < 5;i++){
		uint32_t _paget[1024] __attribute__((aligned(4096)));
		for(int j = 0; j < 1024;j++,addr+=4096){
			_paget[j] = addr | 0b11;
		}
		paged[i] = (uint32_t)_paget | 0b11;
	}
	ldpgd(paged);
	puts("Paging enabled\n");
	map_page(0x010000000,0xC0000000);

}
int pgalloc(){
	for(int i = 0; i < 1024;i++)
		if(paged[i] == 1)
			return i;
	return -1;
}
/*
 * Load page directory
 */
void ldpgd(uint32_t * p){
	asm("mov %0,%%eax" : : "m"(p));
	asm("mov %eax,%cr3");
	asm("mov %cr0,%eax");
	asm("or $0x80000001,%eax");
	asm("mov %eax,%cr0");

}
void map_page(uint32_t paddr,uint32_t vaddr){
	uint32_t indx = vaddr/1024/4096;
	uint32_t pt[1024]__attribute__((aligned(4096)));
	uint32_t addr = paddr;
	for(int i = 0; i < 1024;i++,addr+=4096){
		pt[i] = addr | 3;
	}
	if(paged[indx] != 1)
		return;
	paged[indx] = (uint32_t)pt|3;

	debug("paget","Registered page directory");
}
void *alloc_page(uint32_t vaddr){
	uint8_t *buf = malloc(4096*1024);

	map_page((uint32_t)buf,vaddr);
	return buf;
}
