#ifndef __BMP_H
#define __BMP_H
//offset 0x00
struct Bmp_Hdr{
	uint16_t ignore; //Signature 0x42 0x4d
	uint32_t size;//Size of file in bytes
	uint16_t reserved;
	uint16_t reserved; 
	uint32_t offset;//Pixel array offset
};
//offset 0x0e
struct Dit_Hdr{
	uint32_t hdrsize;//Size of header
	uint16_t width;//Width of bitmap
	uint16_t height;//Height of bitmap
	uint16_t color;//must be one
	uint16_t bpp;//bits per pixel
	uint32_t compression;
	uint32_t image_size;
	uint32_t horizontalRes;
	uint32_t verticalRes;
	uint32_t nColors;
	uint32_t important;
}

#endif
