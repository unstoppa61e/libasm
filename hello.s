section .data

message: db "hello", 10

section .text

global _main
_main:
	xor rax, rax
	mov rax, 0x2000004
	mov	rdi, 1
_break1:
	mov rsi, message
	mov rdx, 6
	syscall
	ret