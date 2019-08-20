#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
int main(int argc,char *argv[]){
	if(argc < 2){
		return -1;
	}
	exec(argv[1],argc-1,&argv[1]);
	return 0;
}
