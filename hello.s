section .data
	msg db 'Hello, world!', 0x0a
	len equ $ - msg

section .text
	global _main
_main:
	; SYSCALL: write(1, msg, len);
	mov rax, 0x2000004	; write の番号
	mov rdi, 1			; 1
	mov rsi, msg		; 2
	mov rdx, len		; 3
	syscall

	; SYSCALL: exit(0)
	mov rax, 0x2000001	; exit の番号
	mov rdi, 0			; 1
	syscall