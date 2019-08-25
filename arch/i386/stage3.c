#include <llfs.h>
#include <lib.h>
#include <tmpfs.h>
#include <video.h>
#include <stdint.h>
void bzero(void *buf,unsigned int n){
	for(int i = 0; i < n;i++)
		*((uint8_t*)buf + n) = 0;
}
int main(){
	clear();
	char *buf = malloc(1024);
	puts("Looking for boot disk...");
	*(uint8_t*)0x600 = 0xc3;
	uint8_t slavebit = -1;
	uint16_t drive = -1;
	int8_t a = ata_read_master(buf,1,0x1f0,0xe0);
	if(a == 0){

		if(memcmp(buf,"WORM",4) == 0){
			drive = 0x1f0;
			slavebit = 0xe0;
			goto b;
		}
	}
	bzero(buf,512);
	a = ata_read_master(buf,1,0x1f0,0xf0);
	if(a == 0){
		if(memcmp(buf,"WORM",4) == 0){
			drive = 0x1f0;
			slavebit = 0xf0;
			goto b;
		}
	}
	bzero(buf,512);
	a = ata_read_master(buf,1,0x170,0xe0);
	if(a == 0){
		if(memcmp(buf,"WORM",4) == 0){
			drive = 0x170;
			slavebit = 0xe0;
			goto b;
		}
	}
	bzero(buf,512);

	a = ata_read_master(buf,1,0x170,0xf0);
	if(a == 0){
		if(memcmp(buf,"WORM",4) == 0){
			drive = 0x170;
			slavebit = 0xe0;
			goto b;
		}
	}
	panic("No devices found");
b:;	*(uint16_t*)0x100 = drive;
  	*(uint8_t *)0x102 = slavebit;
	free(buf); 
	buf = malloc(512);
  	 a = ata_read_master(buf,0,*(uint16_t*)0x100,*(uint8_t*)0x102);
	if(a != 0)
		panic("I/O Error");
	*(uint32_t*)0x103 = *(uint32_t*)(buf + 0x1be);
	putx(*(uint32_t*)0x103);
  //    	puts("Loading kernel...");
	char *arr[] = {"/utd_kern"};
	exec("/utd_kern",1,arr);
  	panic("No devices found");


}
void breakpoint(){
	*(uint8_t*)0x600 = 0xc3;
	void (*func)() = 0x600;
	func();
}
void panic(char *message){
	puts("\npanic(");
	puts(message);
	puts(")\nA fatal error has occured.\n");
	while(1){
		asm("hlt");
	}

}

