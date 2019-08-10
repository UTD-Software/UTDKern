#ifndef __STDIO_H
#define __STDIO_H
#define STDIN 0
#include <llfs.h>
#include <stdint.h>
struct Entry * _opendir(const char *dir);
void readSector(char *buf,uint32_t lba);
void puts(const char *str);
char getc(int fd);
void putc(char c);
void putx(int c);
char *gets();
#endif
