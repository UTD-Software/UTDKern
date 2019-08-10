CC=i386-elf-gcc
CFLAGS=-nostdlib -ffreestanding -Ilibc/include
LDFLAGS=-lc -Llibc
all:
	@make -C libc
	@echo "(CC) ${PWD}/../usr/bin/ls"
	@${CC} ls.c -o ../usr/bin/ls ${CFLAGS} ${LDFLAGS}
	@echo "(CC) ${PWD}/../usr/bin/err"
	@${CC} err.c -o ../usr/bin/err ${CFLAGS}
	@echo "(CC) ${PWD}/../init"
	@${CC} init.c -o ../init ${CFLAGS} ${LDFLAGS} -Tlinker.ld
	@echo "(CC) ${PWD}/../usr/bin/echo"
	@${CC} echo.c -o ../usr/bin/echo ${CFLAGS} ${LDFLAGS} -Tlinker.2.ld
	@echo "(CC) ${PWD}/../usr/bin/memdump"
	@${CC} memdump.c -o ../usr/bin/memdump ${CFLAGS} ${LDFLAGS} -Tlinker.2.ld
