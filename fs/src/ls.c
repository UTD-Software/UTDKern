#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <llfs.h>
int main(int argc,char *argv[]){
	if(argc < 2)
		return -1;
	struct Entry *dir = _opendir(strcmp(argv[1],"/") == 0 ? "" : argv[1]);
	uint8_t *buf = malloc(512);

	readSector(buf,dir->nxtlba);
	memcpy(dir,buf,sizeof(*dir));
	char *prevname = malloc(1024);
	bzero(prevname,1024);
	while(1){
		memcpy(dir,buf,sizeof(*dir));
		if(strcmp(prevname,buf + sizeof(*dir)) != 0){
			puts(buf + sizeof(*dir));
			puts(" ");
		}
		strcpy(prevname,buf + sizeof(*dir));
		if(dir->contlba == 0)
			break;
		readSector(buf,dir->contlba);

	}
	return 0;
}
