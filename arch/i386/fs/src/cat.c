#include <stdio.h>
#include <stdlib.h>
int main(int argc,char *argv[]){
	if(argc < 2)
		return -1;
	for(int i = 1; i < argc;i++){
		int fd = open(argv[i],O_RDONLY);
		if(fd < 0)
			return -1;
		char c;
		while((read(fd,&c,1) == 1)){
			putc(c);
		}
	}
	return 0;
}
