/*
 * Stage1 ELF loader
 * Zachary James Schlotman
 * WORM Bootloader
 */
#include <elf.h>
#include <string.h>
#include <lib.h>
#ifdef __STANDALONE
//Executes stage 3 bootloader
void load_stage_3(){
	void *pntr = (void*)0xA000;//Creat pointer to file data
	Elf32_Ehdr *ehdr = (Elf32_Ehdr*)0xA000;
	Elf32_Phdr *phdr = (Elf32_Phdr*)(0xA000 + (uint16_t)ehdr->e_phoff);
	void (*func)();
	int i = 0;
	//Parse elf and move Loadable Phdrs into memory
	for( i = 0; i < ehdr->e_phnum;i++){
		if((uint16_t)phdr[i].p_type == PT_LOAD)
			memcpy((uint16_t*)phdr[i].p_vaddr,(uint8_t*)pntr + (uint16_t)phdr[i].p_offset,phdr[i].p_memsz);
	}
	func = (void*)ehdr->e_entry;
	func();
}
//I should probably just compile bzero.c into the kernel
void bzero(void *pntr,unsigned int n){
	for(int i = 0; i < n;i++)
		*((uint8_t*)pntr + i)= 0;
}
//Remnents from the early days

void _io_error(){

	*(uint8_t*)0xb8000 = 'E';
	*(uint8_t*)0xb8001 = 15;
}
#endif
#ifndef __STANDALONE
void panic(){
	puts("BL_PANIC");
	while(1);
}
//Loads the file into memory
void load_stage3_1(){
	uint8_t *buf = 0xA000;
	char sig[5];
	uint8_t i;
	for(i = 1; i < 63;i++){
		bzero(buf,512);
		bios_readdisk(buf,*(uint8_t*)0x50,0,i,0);
		
		if(buf[0] == 0x7f && buf[1] == 'W' && buf[2] == 'O' && buf[3] == 'R' && buf[4] == 'M'){
			 _bios_readdisk(0xA000,*(uint8_t*)0x50,47,0,0,i+buf[5]+1);
			//if(ret < 0)
			//	puts("Error");
			_bios_readdisk(0xF000,*(uint8_t*)0x50,buf[5],0,0,i+1);
			puts("Exec\n");
			break;
		}
		if(i == 62)
			panic();
	}
	puts("Going protected...\n");
	go_protected();

}
#endif
