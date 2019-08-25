#ifndef __LIB_H
#define __LIB_H
#ifndef BCC
#include <stdint.h>
#else
#include "_stdint.h"
#endif
#define O_RDONLY 1
#define O_WRONLY 2
#define STDIN 0
#define O_RDWR 3
void breakpoint();
void enterV8086();
void exitV8086();
void getFreeLine();
void debug(const char *a,const char *b);
unsigned char getc(int fd);
void outw(uint16_t port,uint16_t val);
int open(const char *path,int o);
int llread(int fd,char *buf,unsigned int n);
extern void putc(char c);
extern void puts(const char *str);
void bzero(void *pntr,unsigned int n);
#ifdef __PM
#ifndef __SLIB_H
#define __SLIB_H
unsigned int strlen(const char *str);
void *memcpy(void *dest,const void *src,unsigned int n);
char *strcpy(char *dest,const char *src);
int strcmp(const char *str,const char *str1);
#endif
#endif
int fsize(int fd);
void idenpage(uint32_t addr);
void idt();
void putx(int n);
void puti(int n);
void scroll();
void exec(const char *dest,int argc,char *argv[]);
void move_cursor(uint8_t a,uint8_t b);
void panic();
int pow(int a,int b);
struct Mem{
	uint8_t alloc;
#ifndef __PM
	uint16_t size;
#else
	uint32_t size;
#endif
};
struct CHS{
	uint16_t c;
	uint16_t h;
	uint8_t s;
};
struct llfd{
	struct Entry *pntr;
	struct llfd *nxt;
	uint8_t t;
};
struct llfd *getAddressSpace();
int ata_read_master(void *buf,unsigned int lba,unsigned short drive,unsigned char slavebyte);
void int10h_ldr();
short bios_readdisk(void *pntr,uint8_t drive,uint8_t head,uint8_t sector,uint8_t cylinder);
void _bios_readdisk(void *pntr,uint8_t drive,uint8_t tsect,uint8_t c,uint8_t h,uint8_t s);
uint8_t inb(uint16_t io);
uint16_t inw(uint16_t io);
void outb(uint16_t io,uint8_t v);
char *x2p(int i);
#endif
