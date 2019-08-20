/*
 * Final signature writer
 * (c) 2019 Zachary James Schlotman
 */
#include <stdio.h>
#include <stdlib.h>
int main(int argc,char *argv[]){
	if(argc != 3)
		return -1;
	FILE *in = fopen(argv[2],"rb");
	FILE *out = fopen(argv[1],"r+b");
	fseek(in,0,SEEK_END);
	int size = ftell(in) / 512;
	char *buf = malloc(6);
	fread(buf,1,6,out);
	buf[5] = size;
	fseek(out,0,SEEK_SET);
	fwrite(buf,1,6,out);
	fclose(in);
	fclose(out);
	return 0;
}
