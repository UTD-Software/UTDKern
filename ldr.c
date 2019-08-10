
#include <lib.h>
#include <stdint.h>
#include <elf.h>
#include <llfs.h>
#include <mem.h>
#include <string.h>
#include <kern.h>
//Wrapper for some fancy smansh assembly code I wrote to enter and leave real mode. This is mostly for my vesa driver
void int10h_ldr(){
	int fd = open(INT10H_KO,O_RDWR);
	if(fd <0){
		panic("Unable to set video mode: Missing kernel object");
	}
	void *pntr = (void*)0x7c00;
	llread(fd,pntr,fsize(fd));
	void (*func)() = pntr;
}
//Name says it. Specify path, argument count, and array of arguments
void exec(const char *path,int argc, char *argv[]){
#ifdef DEBUG
	debug("pgrmldr",path);
#endif

	int fd = open(path,O_RDWR);
	if(fd < 0)
		return;
	uint8_t *buf = malloc(fsize(fd));

	int r = llread(fd,buf,fsize(fd));
	Elf32_Ehdr *ehdr = (Elf32_Ehdr *)buf;
	Elf32_Phdr *phdr = (Elf32_Phdr *)(buf + ehdr->e_phoff);
	int size = 0;

	for(int i = 0; i < ehdr->e_phnum;i++){
		alloc_page(phdr[i].p_paddr);
		memcpy((void*)(phdr[i].p_paddr),buf + phdr[i].p_offset,phdr[i].p_memsz);
#ifdef DEBUG
		puts("{");
		putx((uint32_t)(buf + phdr[i].p_offset));
		puts("->");
		putx(phdr[i].p_vaddr);
		puts("}.");
		putx(phdr[i].p_memsz);
		puts("\n");
#endif
	}

	void (*func)()= (void (*))(ehdr->e_entry);

	breakpoint();
	program_memory_init();
	*userbit = 1;
	func(argc,argv);
	*userbit = 0;
	program_memory_destroy();
	breakpoint();
}
