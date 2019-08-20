#include <debug.h>
void breakpoint(){
	void (*func)() = 0x600;
	func();
}
