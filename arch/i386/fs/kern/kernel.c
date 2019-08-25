#include <kernel/io.h>
#include <kernel/mem.h>
void panic(const char *msg){
	puts("panic(");
	puts(msg);
	puts(")");
}
int main(int argc,char *argv[]){
	clear();
	puts("Stub Kernel\n");
	while(1);
}
