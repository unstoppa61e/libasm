global _ft_strlen

section .text
_ft_strlen:
	xor rax, rax

.while:
	cmp	byte[rdi + rax], 0
	je	.endwhile
	inc rax
	jmp .while

.endwhile:
	ret