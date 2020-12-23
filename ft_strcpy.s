global _ft_strcpy

section .text
_ft_strcpy:
	xor rax, rax
	push rax

.loop:
	cmp byte [rsi + rax], 0
	je	.end
	mov	cl, [rsi + rax] 
	mov	[rdi + rax], cl
	inc rax
	jmp .loop

.end:
	mov byte [rdi + rax], 0
	pop rax
	ret