section .data
msg:db 'I/O Error',0xa,0
section .text
global _bios_readdisk
extern _puts
extern _io_error
_bios_readdisk:
push bp
mov bp,sp
mov ax,ds
mov es,ax
mov ah,0x02
mov al,1
mov bx,[bp+4]
mov dl,[bp+6]
mov dh,[bp+8]
mov cl,[bp+10]
mov ch,[bp+12]
int 0x13
cmp ax,1
je r
call io_error
r:pop bp
ret
global __bios_readdisk
__bios_readdisk:
push bp
mov bp,sp
mov ax,ds
mov es,ax
mov ah,0x02
mov dl,[bp+6]
mov bx,[bp+4]
mov al,[bp+8]
mov ch,[bp+10]
mov dh,[bp+12]
mov cl,[bp+14]
int 0x13
cmp ah,0
je r
call io_error
jmp r
io_error:
mov ah,0x0e
mov al,'E'
int 0x10
hng:jmp hng
