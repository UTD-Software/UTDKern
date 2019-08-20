#include <libbmp.h>
#include <libvesa.h>
int ceil(double d){
	if(d-(int)d < 0.03125){
		return d;
	}
	return d+1;
}
int displaySplash(void *pntr){
	struct Bmp_Hdr *bmp = (struct Bmp_Hdr *)pntr;
	struct Dit_Hdr *dit = (struct Dit_Hdr *)(pntr + 0x0e);
	void *data = pntr + 0x0e + dit->hdrsize;
	int rsize = ceil(24.0*bmp->width/32);
	int csize = ceil(24.0*height/32);
	for(int i = 0; i < rsize;i++)
		for(int j = 0; j < csize;j++)
			plot_pixel(*(uint32_t*)(pntr + 0x0e + dit->hdrsize) + i * csize * 4 + j * 4,j,i); 
}
