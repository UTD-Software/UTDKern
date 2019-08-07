#include <lib.h>
#include <stdint.h>
#include <elf.h>
#include <llfs.h>
#include <mem.h>
#include <string.h>
#include <kern.h>
void int10h_ldr(){
	int fd = open(INT10H_KO,O_RDWR);
	if(fd <0){
		panic("Unable to set video mode: Missing kernel object");
	}
	void *pntr = (void*)0x7c00;
	llread(fd,pntr,fsize(fd));
	void (*func)() = pntr;
//	func();
}
void exec(const char *path,int argc, char *argv[]){
#ifdef DEBUG
	puts("exec(");
	puts(path);
	puts(")");
#endif

	int fd = open(path,O_RDWR);
	if(fd < 0)
		return;
	uint8_t *buf = malloc(fsize(fd));

	int r = llread(fd,buf,fsize(fd));
//	putx(fsize(fd));
	Elf32_Ehdr *ehdr = (Elf32_Ehdr *)buf;
	Elf32_Phdr *phdr = (Elf32_Phdr *)(buf + ehdr->e_phoff);
	int size = 0;

	map_page(phdr[0].p_paddr,phdr[0].p_vaddr);
	for(int i = 0; i < ehdr->e_phnum;i++){
		memcpy((void*)(phdr[i].p_paddr),buf + phdr[i].p_offset,phdr[i].p_memsz);
#ifdef DEBUG
		puts("{0x");
		putx((uint32_t)(buf + phdr[i].p_offset));
		puts("->0x");
		putx(phdr[i].p_vaddr);
		puts("}.");
		putx(phdr[i].p_memsz);
		puts("\n");
#endif
	}

	void (*func)()= (void (*))(ehdr->e_entry);
#ifdef DEBUG
	puts("(");
	puts(path);
	puts(")");
	puts("->0x");
	putx(ehdr->e_entry);

	puts("\n");
#endif
//	void **pntrarr = (void**)0x1000;
//	*(uint8_t*)0x999 = 2;
//	*(uint32_t*)0x1000 = argc;
//	*(uint32_t*)0x1004 = (uint32_t)argv;
	breakpoint();
	func(argc,argv);
	breakpoint();
}
