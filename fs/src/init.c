#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <debug.h>
int main(int argc,char *argv[]){
	breakpoint();
	debug("init","primitive init system not implemented, dropping into shell instead");
	while(1){
		puts(">");
		char *command = gets(STDIN);
		char **arr = sep(command,' ');
		int k = 0;
		while(arr[k] != 0)
			k++;

		char *path = malloc(1024);
		strcpy(path,"/usr/bin/");
		strcat(path,arr[0]);
		if(arr[0][0] == 0)
			goto b;
		exec(path,k,arr);
b:;		breakpoint();
		free(arr);
		puts("\n");
	}
	return 0;
}
