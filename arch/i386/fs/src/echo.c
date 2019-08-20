#include <stdio.h>
#include <stdlib.h>
int main(int argc, char *argv[]){
//	putx(argc);
	breakpoint();
	for(int i = 1; i < argc;i++){
		puts(argv[i]);
		breakpoint();
		puts(" ");
	}
	breakpoint();
	return 0;
}
