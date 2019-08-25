#include "lib.h"
#include <stdint.h>
#include "mem.h"
uint32_t paged[1024] __attribute__((aligned(4096)));
//uint32_t paged __attribute__((aligned(4096))) = (uint32_t **)0x9000;
uint32_t curraddr;
uint32_t naddr;
struct Stack{
	uint32_t paget;
	uint32_t indx;
	struct Stack *nxt;
};
void flush();
void ldpgd(uint32_t *p);
struct Stack *stack = (struct Stack *)0x2000;
void pushp(uint32_t paget,uint32_t indx){
	struct Stack new;
	new.paget = paget;
	new.indx = indx;
	new.nxt = stack;
	*stack = new;
}
struct llmem{
	uint8_t alloc;
	uint32_t size;
}__attribute__((packed));
void *llmalloc(uint32_t size){
	void *pntr = (void*)0x3000;
	while(pntr < (void*)(4096*1024)){
		if(*(uint8_t*)pntr == 1)
			pntr+=sizeof(struct llmem)+*(uint32_t*)(pntr+1);
		else{
			*(uint32_t*)(pntr + 1) = size;
			*(uint8_t*)pntr = 1;
			return pntr+sizeof(struct llmem);
		}
	}
}
uint32_t popp(uint32_t indx){
	uint32_t ret;
	struct Stack *save = stack;
	while(stack->nxt->indx != indx && stack->nxt != 0){
		stack = stack->nxt;
	}
	if(stack->nxt == 0)
		return 0;
	ret = stack->nxt->paget;
	stack->nxt = stack->nxt->nxt;
	return ret;
}
/*
 *Initializing paging
 */

void init_page(){
	int addr = 0;
	for(int i = 0; i < 1024;i++)
		paged[i] = 1;
	uint32_t paget[1024] __attribute__((aligned(4096)));
	for(int i = 0; i < 1024;i++,addr+=4096){
		paget[i] = addr | 0b11;
	}
	paged[0] = 0b11 | (uint32_t)paget;
//	addr = 0x00800000;
	uint32_t _paget[1024]__attribute__((aligned(4096)));
	for(int i = 0; i < 1024;i++,addr+=4096){
		_paget[i] = addr | 3;
	}
	paged[1] = 0b11 | (uint32_t)_paget;
	int i = 0;
	paged[1023] = (uint32_t)&paged[1023] | 3;
	ldpgd(paged);
	puts("Paging enabled\n");
	map_page(0x04000000,0x04000000);
	curraddr = 0x00F00000;
	naddr = curraddr+4096*1024;
	puts("Initial memory setup complete\n");
}
void *getPD(){
	return (void*)0xFFFFF000;
}int pgalloc(){
//	uint32_t * pd = (uint32_t *)getPD();
	for(int i = 0; i < 1024;i++)
		if(paged[i] == 1)
			return i;
	return -1;
}
void displayPD(){
	for(int i = 0; i < 1024/0x10;i++){
		putx(i*0x10);
		puts(":");
		for(int j = 0; j < 0x10;j++){
			putx(*(uint32_t*)(getPD() + i*0x40+j*4));
			puts(" ");
		}
		puts("\n");
	}
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
void populate(){
	uint32_t *paged = (uint32_t*)0xFFFFF000;
	for(int i = 0; i < 1024;i++){
		paged[i] = *(uint32_t*)(0xFFFFF000 + i * 4);
	}	
}
void map_page(uint32_t paddr,uint32_t vaddr){
	uint32_t * pd = (uint32_t *)0xFFFFF000;
	uint32_t indx = vaddr>>22;
	uint32_t addr = paddr;
	uint32_t *pt = ((uint32_t *)0xFFC00000) + ((indx << 10));
	if(pd[indx] != 1)
		return;
	for(int i = 0; i < 1024;i++,addr+=4096)
		pt[i] = addr | 3;

	pd[indx] = (uint32_t)pt | 3;
	flush();
	debug("paget","Registered page directory");
}

void flush(){
	asm("mov %cr3,%eax");
	asm("mov %eax,%cr3");
}
void alloc_page(uint32_t vaddr){
	uint32_t * pd = (uint32_t *)getPD();
	uint32_t pt[1024]__attribute__((aligned(4096)));
	for(int i = 0; i < 1024;i++,naddr+=4096){
		pt[i] = naddr | 0b11;
	}
	if(paged[vaddr/1024/4096] == 1){
		paged[vaddr/1024/4096]=(uint32_t)pt|0b11;
		flush();
	}
}

void *allocNewPage(){
	uint32_t indx = 0;
	uint32_t * pd = (uint32_t *)0xFFFFF000;	
	while(pd[indx] != 1 && indx < 1024){
		indx++;
	}
	if(indx == 1024)
		return 0;
	uint32_t *pt = ((uint32_t*)(0xFFC00000) + (indx << 10));
	for(int i = 0; i < 1024;naddr+=4096,i++)
		pt[i] = naddr | 3;

	pd[indx] = (uint32_t)pt | 3;
	flush();
	return (void*)(indx*4096*1024);
}

void program_memory_init(){
	*usermem = allocNewPage();
	if(!(*usermem))
		panic("Failed to allocate user memory");
	for(int i =0; i < 4096*1024;i++)
		*usermem[i] = 0;
}
void program_memory_set(uint32_t size){

}
void program_memory_destroy(){
	dealloc_page((uint32_t)*usermem);
}
void dealloc_page(uint32_t addr){
	populate();
	uint32_t * pd = (uint32_t *)getPD();
	paged[addr/4096/1024] = 1;
	flush();
}
