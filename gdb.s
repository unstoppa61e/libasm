global _main

section .data
message: db "hoge"

section .text
_main:
	xor rax, rax
	mov  rdi, message

.loop:
	cmp	byte [rdi + rax], 0
	je	.end
	inc rax
	jmp .loop

.end:
	ret