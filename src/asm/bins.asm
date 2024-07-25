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
