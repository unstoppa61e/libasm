global _main

section .data
s1 db "hogehoge", 0

section .text
_main:
	mov rdi, s1

	xor rax, rax

.while:
	cmp	byte[rdi + rax], 0
	je	.endwhile
	inc rax
	jmp .while

.endwhile:
	ret