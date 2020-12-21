
section .data
str: db 'hello hello', 10

section .text
global _main
_main:
	mov rax, 0x2000004

	mov rdi, 1
	mov rsi, str
	mov rdx, 12
	syscall
	ret