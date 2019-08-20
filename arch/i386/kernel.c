/*
 * Kernel Space handler
 * (c) 2019 Zachary James Schlotman
 * IDK i'll implement it tomorrow or something
 */
#include <kernelspace.h>
struct StoragePntr *allocSP(){
	struct StoragePntr *ret = (struct StoragePntr *)0x800000;
	while(ret->nxt != 0 && ret < 0xC00000)
		ret = ret->nxt;
	if(ret == 0xC00000)
		return 0;
	return ret;
}

