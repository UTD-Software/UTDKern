OBJS=puts.o open.o clear.o crt0.o read.o malloc.o opendir.o exec.o crti.o debug.o readSector.o crtn.o breakpoint.o putc.o sep.o bzero.o putx.o string.o gets.o getc.o free.o
LIBS=libc.a
CC=i386-elf-gcc
AS=nasm
AR=i386-elf-ar
CFLAGS=-Iinclude -nostdlib -ffreestanding
all:
	@rm -f *.a *.o
	@echo "(CC) ${PWD}/debug.o"
	@${CC} -c debug.c -o debug.o ${CFLAGS}
	@echo "(AS) ${PWD}/crti.o"
	@${AS} -f elf crti.asm -o crti.o
	@echo "(AS) ${PWD}/crtn.o"
	@${AS} -f elf crtn.asm -o crtn.o
	@echo "(CC) ${PWD}/sep.o"
	@${CC} -c sep.c -o sep.o ${CFLAGS}
	@echo "(CC) ${PWD}/string.o"
	@${CC} -c string.c -o string.o ${CFLAGS}
	@echo "(CC) ${PWD}/puts.o"
	@${CC} -c puts.c -o puts.o ${CFLAGS}
	@echo "(CC) ${PWD}/bzero.o"
	@${CC} -c bzero.c -o bzero.o ${CFLAGS}
	@echo "(CC) ${PWD}/crt0.o"
	@${CC} -c  crt0.c -o crt0.o ${CFLAGS}  -Werror
	@echo "(CC) ${PWD}/gets.o"
	@${CC} -c gets.c -o gets.o ${CFLAGS}
	@echo "(CC) ${PWD}/getc.o"
	@${CC} -c getc.c -o getc.o ${CFLAGS}
	@echo "(CC) ${PWD}/free.o"
	@${CC} -c free.c -o free.o ${CFLAGS}
	@echo "(CC) ${PWD}/malloc.o"
	@${CC} -c malloc.c -o malloc.o ${CFLAGS}
	@echo "(CC) ${PWD}/exec.o"
	@${CC} -c exec.c -o exec.o ${CFLAGS}
	@echo "(CC) ${PWD}/putc.o"
	@${CC} -c putc.c -o putc.o ${CFLAGS}
	@echo "(CC) ${PWD}/putx.o"
	@${CC} -c putx.c -o putx.o ${CFLAGS}
	@echo "(CC) ${PWD}/breakpoint.o"
	@${CC} -c breakpoint.c -o breakpoint.o ${CFLAGS}
	@echo "(CC) ${PWD}/opendir.o"
	@${CC} -c opendir.c -o opendir.o ${CFLAGS}
	@echo "(CC) ${PWD}/readSector.o"
	@${CC} -c readSector.c -o readSector.o ${CFLAGS}
	@echo "(CC) ${PWD}/read.o"
	@${CC} -c read.c -o read.o ${CFLAGS}
	@echo "(CC) ${PWD}/clear.o"
	@${CC} -c clear.c -o clear.o ${CFLAGS}
	@echo "(CC) ${PWD}/open.o"
	@${CC} -c open.c -o open.o ${CFLAGS}
	@echo "(AR) ${PWD}/libc.a"
	@${AR} rcs libc.a ${OBJS}
install:
	cp crt0.o /usr/local/lib/i386-elf
	cp libc.a /usr/local/lib
