#ifndef __MEM_H
#define __MEM_H
#ifdef __PM
#include <stdint.h>

static uint8_t **usermem;
#endif
void *malloc(unsigned long n);
void free(void *pntr);
#ifdef __PM
void map_page(uint32_t paddr,uint32_t vaddr);
void alloc_page(uint32_t vaddr);
void iden_page(uint32_t addr);
void memory_init();
void program_memory_init();
void program_memory_destroy();
void dealloc_page(uint32_t addr);
static uint32_t *userbit;
void displayPD();
#endif
#endif
