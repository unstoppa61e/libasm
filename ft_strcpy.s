global _ft_strcpy

section .text
_ft_strcpy:
	xor rax, rax			; index = 0;
.while:
	mov cl, [rsi + rax]		; c = src[index]
	mov [rdi + rax], cl		; dst [index] = c;
	cmp byte[rsi + rax], 0  ; if (src[index] - 0
	je .endwhile			; == 0) goto .endwhile
	inc rax					; index++;
	jmp .while				; goto .while

.endwhile:
	mov rax, rsi			; to return the src
	ret