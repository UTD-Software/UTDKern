[bits 16]
[org 0x7c00]
mov byte [0x50],dl
mov ah,0
mov al,3
int 0x10
xor eax,eax
xor ebx,ebx
xor edx,edx
xor ecx,ecx
xor sp,sp
xor bp,bp
xor si,si
xor di,di

mov sp,0xffff
mov bp,sp
mov dl,[0x50] 
mov ah,2
mov al,2
mov ch,0
mov cl,2
mov dh,0
mov bx,0x1000
int 0x13
jmp 0x1004
times 510 - ($ - $$) db 0
dw 0xaa55
