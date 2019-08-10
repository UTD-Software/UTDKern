
#ifndef __STRING_H
#define __STRING_H

void strncpy(char *dest,const char *src,unsigned int n);
int strncmp(const char *one,const char *two,unsigned int n);
#ifndef __SLIB_H
#define __SLIB_H
void memcpy(void *dest,const void *src,unsigned int n);
void strcpy(char *dest,const char *src);
void strcat(char *dest,const char *src);
#endif
#endif
