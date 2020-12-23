section .data
books dd 10
counter dq 50
sum dq 30

section .text
global _main
_main:
	mov rax, -1
	mov al, 20
	mov rdx, 15

_break:
	mov dword [rel books], 20
	; mov rax, qword[rel counter]
	mov eax, [rel counter]
	mov [rel counter], rax

	xor rax, rax
	ret