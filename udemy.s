section .data
counter	dq	10

section .text
global _main
_main:
	mov rbp, rsp
	mov rbx, 50
	mov	[counter],rbx
	xor rax, rax
	ret