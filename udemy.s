global _main

section .data
source db "this is source", 0
length equ $ - source

destination times length db 0

section .text
_main:
	cld ; clear direction flag
	mov rsi, source
	mov rdi, destination
	mov rcx, length ; rcx acts as the counter for 'rep' instruction
	rep movsb

;;;;;;;;;;;;;;;;;;;;;;;;;
	xor rax, rax
	ret