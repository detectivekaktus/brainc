format ELF64 executable

segment executable
entry main
main:
  mov rax, 1
  mov rdi, 1
  mov rsi, hello_world
  mov rdx, 14
  syscall

  mov rax, 60
  mov rdi, 0
  syscall

segment readable writable
hello_world: db "Hello, World!",10
