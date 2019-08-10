/*
 * Malloc shit
 */
#include <mem.h>
#include <lib.h>
#ifdef __PM
void memory_init(){
	for(int i = 0xC0000000; i < 0xC0400000;i++)
		*(uint32_t*)i = 0;
}
#endif
#ifndef __PM
void *malloc(unsigned short size){
	struct Mem *pntr = (struct Mem*)0x9000;
	void *ret;
	while(1){
		if((pntr+size) < 0x9000){/*Overflow protection*/

			puts("OUT OF MEMORY!!!!\n");
//			puts("Cannot allocate size: 0x");
//			putx(size);
		}
		if(pntr->alloc){
			pntr+=sizeof(*pntr)+pntr->size;
			continue;
		}
		if(pntr->size >= (size)){
			unsigned short save = pntr->size;
			pntr->size = size;
			pntr->alloc = 1;
		       	ret=pntr + sizeof(*pntr);
			pntr+=size+sizeof(*pntr);
			pntr->alloc = 0;
			pntr->size = save-size;
			return ret;
		}else if(pntr->size != 0){
			pntr+=pntr->size+sizeof(*pntr);
		}else{
			pntr->alloc = 1;
			pntr->size = size;
			return pntr + sizeof(*pntr);
		}
	}
}
#else
void *malloc(unsigned long size){
	if(size == 0)
		return malloc(1);
	struct Mem *pntr = (struct Mem*)(userbit ? usermem : 0xC0000000);
	while(1){
		if(((uint32_t)pntr + size) < (userbit ? usermem : 0xC0000000)){
			puts("Out of memory\n");
			puts("Size:0x");
			putx(size);
			puts(" pntr=0x");
			putx((uint32_t)pntr);
			puts("\n");
			return 0;
		}
		if(pntr->alloc){
			pntr+=sizeof(*pntr)+pntr->size;
			continue;
		}
		if(pntr->alloc != 0){
			puts("A Memory Exception has occured at address:0x");
			putx(pntr);
			puts("!\nReason:Invalid memory structure, running into someone elses memory?");
			panic("mem I/O");
		}
		if(pntr->size == 0){
			pntr->alloc = 1;
			pntr->size = size;
			return pntr + sizeof(*pntr);
		}else
			pntr+=sizeof(*pntr)+pntr->size;
	}
}
#endif
void free(void *mem){
	struct Mem *pntr = (struct Mem*)mem;
	pntr-=sizeof(struct Mem);
#ifdef __PM
	if(pntr->alloc != 1){
		if(pntr->alloc == 0){
			puts("Memory Exception: Double free pntr 0x");
			putx(pntr+sizeof(struct Mem));
			puts("Press any key to continue\n");
			getc(STDIN);
		}else{
			puts("Memory Exception: Freeing Invalid pntr 0x");
			putx(pntr+sizeof(struct Mem));
			puts("Press any key to continue\n");
			getc(STDIN);
		}
	}
#endif
	pntr->alloc = 0;
}
