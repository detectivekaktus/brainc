; In order to link with the stdlib.h, we need to declare an external
; symbol called calloc to allocate some memory for the bytes array
; that's going to be manipulated during the program execution.
;
; There are two parameters expected by the calloc function.
; ESI ----> index register that stores the size of one element
; EDI ----> index register that stores the number of elements to be allocated
extern calloc

; This set of instructions allocates one kilobyte of memory using the
; C standard library function calloc. The pointer returned is stored in the rax
; register.
mov esi, 1
mov edi, 1024
call calloc
mov QWORD PTR [rbp-8], rax

; Instead of relying on the C standard library there's actually a way
; to declare arrays of bytes, integers and long integers.
; The instruction down below shows how to define an array with size of
; 1024 bytes all initialized to zero.
array times 1024 db 0

; There's a double word variable `pos` that keeps the position (0-based
; index) in the bytes array that is manipulated by the end user.
pos dd 0

; To retrieve the effective value of the pos variable defined in the .data
; section we load it into the ebx register. Since pos isn't just a constant
; but a value in the .data section, we need to wrap it with the brackets.
mov ebx, dword [pos]

; To perform increment and decrement operations on bytes it's used the `byte`
; specifier. Here's the assembly equivalent of the following C code, assuming
; that `array` is just an array of chars.
; array[pos] += 5;
add byte [array + ebx], 5

; To update the value of the `pos` variable we need to load it into a register
; and update it accordingly.
mov ebx, dword [pos]
add ebx, 5
mov [pos], ebx
