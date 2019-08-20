#include <stdio.h>
void debug(const char *pstrid,const char *msg){
	puts("[");
	puts(pstrid);
	puts("]:");
	puts(msg);
	puts("\n");
}
