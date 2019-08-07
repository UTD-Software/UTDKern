CC=i386-elf-gcc
AR=i386-elf-ar
CFLAGS=-ffreestanding -nostdlib -I.
VESA_OBJS=libvesa.o
all:
	rm -f *.o *.a
	${CC} -c libvesa.c -o libvesa.o ${CFLAGS} -I..
	${AR} rcs libvesa.a ${VESA_OBJS}
