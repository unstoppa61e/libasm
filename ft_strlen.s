section .text
global _ft_strlen
_ft_strlen:
	xor rax, rax			; index = 0;

.while:
	cmp	byte[rdi + rax], 0	; if (str[index] - 0
	je	.endwhile			; 					 == 0) goto .endwhile
	inc rax					; index++;
	jmp .while				; goto .while

.endwhile:
	ret						; return (index);