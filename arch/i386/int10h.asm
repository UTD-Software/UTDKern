[bits 16]
[org 0x7c00]
section .data
gdt:
limit:dw 0xffff
base:dw 0
db 0
db 0
db 0b10100110
db 0
dw 0xffff
dw 0
db 0
db 0
db 0b10100110
end:
gdtr:
dw end-gdt
dd gdt
idtr:dw 0x3ff
dd 0
section .text

[bits 32]
_eax:dd 0
extern init_page
global int_10
int_10:
mov dword [_eax],eax
cli
mov dword [0x300],esp
mov eax,cr0
and al,0x4000000e
mov cr0,eax
[bits 16]

lgdt [gdtr]
lidt [idtr]
sti
mov eax,[_eax]
int 0x10

mov eax,cr0
or al,1
mov cr0,eax
mov esp,[0x300]
ret
