#include "lib.h"
#include <stdint.h>
#include "mem.h"
uint32_t paged[1024] __attribute__((aligned(4096)));
uint32_t curraddr;
uint32_t naddr;
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
	uint32_t _paget[1024]__attribute__((aligned(4096)));
	for(int i = 0; i < 1024;i++,addr+=4096){
		_paget[i] = addr | 3;
	}
	paged[1] = 0b11 | (uint32_t)_paget;
	ldpgd(paged);
	puts("Paging enabled\n");
	map_page(0x400000,0xC0000000);
	curraddr = 0xF00000;
	naddr = curraddr+4096*1024;
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
//	ldpgd(paged);
	debug("paget","Registered page directory");
}
void alloc_page(uint32_t vaddr){
	uint32_t pt[1024]__attribute__((aligned(4096)));
	for(int i = 0; i < 1024;i++,vaddr+=4096){
		pt[i] = vaddr | 0b11;
	}
	if(paged[vaddr/1024/4096] == 1)
		paged[vaddr/1024/4096]=vaddr|0b11;
//	ldpgd(paged);
}
void *allocNewPage(){
	uint32_t indx = 0;
	for(int i = 0x100; i < 1024;i++)
		if(paged[i] == 1){
			indx = i;
			break;
		}
	uint32_t pt[1024]__attribute__((aligned(4096)));
	for(int i = 0 ; i < 1024;i++,curraddr+=4096){
		pt[i] = curraddr | 3;
	}
	paged[indx] = (uint32_t)pt | 3;
//	ldpgd(paged);
	return (void*)(indx*4096*1024);
}

void program_memory_init(){
	usermem = allocNewPage();
	for(int i =0; i < 4096*1024;i++)
		usermem[i] = 0;
}
void program_memory_set(uint32_t size){

}
void program_memory_destroy(uint32_t addr){
//	dealloc_page(addr);
}
void dealloc_page(uint32_t addr){
	paged[addr/4096/1024] = 1;
}
