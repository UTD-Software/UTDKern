#include <string.h>
#include <vesa.h>
#include <stdint.h>
#define REALPTR(X) (void*)X
#define DIFF(x,y) x-y
uint16_t getMode(int x, int y, int d)
{
	struct VbeInfoBlock *ctrl = (struct VbeInfoBlock *)0x2000;
	struct ModeInfoBlock *inf = (struct ModeInfoBlock *)0x3000;
	uint16_t *modes;
	int i;
	uint16_t best = 0x13;
	int pixdiff, bestpixdiff = DIFF(320 * 200, x * y);
	int depthdiff, bestdepthdiff = 8 >= d ? 8 - d : (d - 8) * 2;

	strncpy(ctrl->VbeSignature, "VBE2", 4);
//	intV86(0x10, "ax,es:di", 0x4F00, 0, ctrl); // Get Controller Info
	breakpoint();
	asm("mov $0x4f00,%ax");
	asm("mov %0,%%di" : :"m"(ctrl));
	int10h_ldr();
//	if ( (uint16_t)v86.tss.eax != 0x004F ) return best;

	modes = (uint16_t*)REALPTR(ctrl->VideoModePtr);
	for ( i = 0 ; modes[i] != 0xFFFF ; ++i ) {
//		intV86(0x10, "ax,cx,es:di", 0x4F01, modes[i], 0, inf); // Get Mode Info
		asm("mov $0x4F01,%ax");
		asm("mov %0,%%cx" : :"m"(modes[i]));
//		asm("mov $0,%es");
		asm("mov %0,%%di" : :"m"(inf));
		int10h_ldr();
//		if ( (uint16_t)v86.tss.eax != 0x004F ) continue;

//		Check if this is a graphics mode with linear frame buffer support
			if ( (inf->attributes & 0x90) != 0x90 ) continue;

		// Check if this is a packed pixel or direct color mode
		if ( inf->memory_model != 4 && inf->memory_model != 6 ) continue;

		// Check if this is exactly the mode we're looking for
		if ( x == inf->Xres && y == inf->Yres &&
				d == 24 ) return modes[i];

		// Otherwise, compare to the closest match so far, remember if best
		pixdiff = DIFF(inf->Xres * inf->Yres, x * y);
		depthdiff = (inf->bpp >= d)? inf->bpp - d : (d - inf->bpp) * 2;
		if ( bestpixdiff > pixdiff ||
				(bestpixdiff == pixdiff && bestdepthdiff > depthdiff) ) {
			best = modes[i];
			bestpixdiff = pixdiff;
			bestdepthdiff = depthdiff;
		}
	}
	if ( x == 640 && y == 480 && d == 1 ) return 0x11;
	return best;
}
void setMode(uint16_t n){
	asm("mov $0x4F02,%ax");
	asm("mov %0,%%bx" : : "m"(n));
	int10h_ldr();
}
