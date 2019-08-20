#include "lib.h"
#include "mem.h"
void puts(const char *str){
	unsigned int i = 0;
	while(*(str+i) > 0){
		putc(*(str + i));	
		i++;
	}

	return;
}

int intlen(int i){
	int ret = 0;
	while(i > 0){
		i/=10;
		ret++;
	}
	return ret;
}
void puti(int i){
	int n = intlen(i)-1;
	int j = 0;
	while(i >= 0){
		putc(i/pow(10,intlen(i)-1)+'0');
		n--;
		j++;
		i-=(i/pow(10,intlen(i)-1))*pow(10,intlen(i)-1);
		if(i == 0)
			break;
	}

}
void putb(uint8_t n){
	int i = 0;
	for(i = 0; i < 8;i++){
		putc(((n >> (8-i)) & 1)+'0');
	}
	putc('\n');
}
char getx(unsigned char c){
	if(c <= 9)
		return c + '0';
	else
		return c-10 + 'A';
}
int xlen(int i){
	int ret = 0;
	do{
		i/=16;
		ret++;
	}while(i > 0);
	return ret;
}
void debug(const char *task,const char *info){
#ifdef DEBUG
	getFreeLine();
	puts("[");
	puts(task);
	puts("]:");
	puts(info);
	puts("\n");
#endif
}
#ifdef __PM
char* x2p(int i){
	char *pntr = malloc(xlen(i));
	int size = xlen(i)-1;
	int j =0;
	if(i == 0){
		return "Error";
	}
	while(i >= 0){
		int c = i % 16;
		pntr[size-j] = getx(c);
		j++;
		i/=16;
		if(i == 0)
			break;
	}
	return pntr;
}
void putx(int i){
	puts("0x");
	puts(x2p(i));
}
#endif
