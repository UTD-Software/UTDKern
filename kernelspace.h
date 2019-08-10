/*
 * Deals with how kernel handles userland
 * (c) 2019 Zachary James Schlotman
 * Note:Some of the items described here may not be ever implemented in the kernel. 
 * Security is not my top priority so if this kernel ever becomes anything more than a hobby of mine
 * do not expect security from any of these features. If i want more security I will create a designated
 * interface and run level for that. As of currently the userland doesn't work properly and I am focused
 * on both preparing for the future and fixing the userland. There are still a lot of issues with paging
 * and I am still solving them. This header and file will be focused on dealing with slightly higher level
 * stuff. I have not taken any osdev class so whatever I code may be unique and with that comes inefficencies
 */
#ifndef __KERNELSPACE_H
#define __KERNELSPACE_H
#include <uuid.h>
/*
 * Everything in the kernel space will start with an allocated byte and then a size dword
 */
struct StoragePntr{
	uint8_t alloc;
	uint32_t size;
	void *pntr;
	void *nxt;
	uuid_t uuid;
};
struct StoragePntr *allocSP();
struct MonoProcessTable{
	uint8_t alloc;
	uint32_t size;
	uint32_t pid;
	uint32_t startPage;
	uint32_t endPage;
	uint32_t securityLevel; //Security level
	int fd;//Similar to signals but able to potentially communicate with inside program
	int signal;//For secure programs
	struct MonoProcessTable *nxt;
	uuid_t uuid;
};
#define SL_KERNEL 0
#define SL_INIT 1
#define SL_DAEMON 2
#define SL_OPEN_PROGRAM 3
#define SL_CLOSED_PROGRAM 4
#define SL_SECURE 5
#endif
