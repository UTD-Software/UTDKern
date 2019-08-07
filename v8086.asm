global enterV8086
global exitV8086
section .text
enterV8086:
   mov ebp, esp               ; save stack pointer

   push dword  ss        ; ss
   push dword  esp        ; esp
   pushfd                     ; eflags
   or dword [esp], (1 << 17)  ; set VM flags
   push dword cs        ; cs
   mov eax,[esp]
   push dword  eax      ; eip
   iret
exitV8086:
	iret
