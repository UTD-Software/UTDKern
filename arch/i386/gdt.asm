[bits 16]
gdt:
a:dq 0
code:dw 0xffff
dw 0
db 0
db 0b10011010
db 0b11001111
db 0
data:dw 0xffff
dw 0
db 0
db 0b10010010
db 0b11001111
db 0
end:
gdtr: dw end-a-1
dd gdt
code_seg:dd code-a
data_seg:dd data-a
global _go_protected
global int_10
_go_protected:cli
sidt [0x400]
lgdt [gdtr]
mov eax,cr0
or eax,1
mov cr0,eax
mov esp,0x9000
mov ebp,esp
jmp (code-a):0xf000
bits 32
finish:
mov eax,10h
mov ds,eax
mov ss,eax
mov es,eax
mov fs,eax
mov gs,eax
mov ebp,90000h
mov esp,ebp
mov al,[0xF000]

jmp 0x0000F000
hng:hlt
jmp hng

int_10:
mov dword [0x300],esp
mov eax,cr0
and al,0xfe
mov cr0,eax
lidt [0x400]
;int 0x10
mov eax,cr0
or al,1
mov cr0,eax
mov esp,[0x300]
 
ret
