global _main
section .data
message: db 'hello', 10

section .text
_main:
	xor rax, rax
	mov rdi, message

.loop:
	cmp byte [rdi + rax], 0
	je .end
	inc rax
	jmp .loop

.end:
	mov	rsi, rax
	add rsi, 48
	mov rax, 0x2000004
	mov rdi, 1
	mov rdx, 1
	syscall
	xor rax, rax
	ret