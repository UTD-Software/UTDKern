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
void debug(char *task,char *info){
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
void putx(int i){
	char pntr[xlen(i)];;
	int size = xlen(i)-1;
	int j =0;
	if(i == 0){
		puts("0");
		return;
	}
	while(i >= 0){
		int c = i % 16;
		pntr[size-j] = getx(c);
//		putc(pntr[size-j-1]);
		j++;
		i/=16;
		if(i == 0)
			break;
	}
	puts(pntr);
//	free(pntr);
}
#endif
