#include <libbmp.h>
#include <libvesa.h>
int displaySplash(void *pntr){
	struct Bmp_Hdr *bmp = (struct Bmp_Hdr *)pntr;
	struct Dit_Hdr *dit = (struct Dit_Hdr *)(pntr + 0x0e);
	void *data = pntr + 0x0e + dit->hdrsize;

}
