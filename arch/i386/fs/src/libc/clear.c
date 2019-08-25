#include <stdlib.h>
void clear(){
	asm("pushal");
	asm("mov $0xe,%ah");
	asm("int $0x80");
	asm("popal");
}
