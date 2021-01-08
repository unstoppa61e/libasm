global _main

section .data
value db 1,2,3,4,5

section .text

_main:
	mov al, [rel value + 3] // al = 4
;;;;;;;;;;;;;;;;;;;;;;;;;
	xor rax, rax
	ret