#ifndef __MEM_H
#define __MEM_H
#ifdef __PM
#include <stdint.h>
#endif
void *malloc(unsigned int n);
void free(void *pntr);
void map_page(uint32_t paddr,uint32_t vaddr);
void *alloc_page(uint32_t vaddr);
#endif
