global _main

; section .data
data dq 100

section .text
; default rel
_main:
	mov qword[rel data], 10
	; mov rax, [data]
	; mov rax, [rel data]
;;;;;;;;;;;;;;;;;;;;;;;;;
	xor rax, rax
	ret