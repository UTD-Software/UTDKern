CC=i386-elf-gcc
CFLAGS=-Iinclude -nostdlib -ffreestanding
LDFLAGS=-L../usr/lib -lk -nostdlib
all:
	${CC} -c kernel.c -o kernel.o ${CFLAGS}
	${CC} kernel.o -o ../utd_kern ${LDFLAGS}
