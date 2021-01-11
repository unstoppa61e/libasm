global _ft_strcmp

; section .data
; s1 dq "stA", 0
; s2 dq "stZ", 0

section .text
; global _main
; _main:
; mov rdi, s1
; mov rsi, s2

_ft_strcmp:
	xor rax, rax			; index = 0;
.while:
	mov al, byte[rdi + rax]
	cmp al, 0
	je .endwhile			; == 0) goto .endwhile
	mov bl, byte[rsi + rax]
	cmp bl, 0
	je .endwhile			; == 0) goto .endwhile
	cmp al, bl
	jne .endwhile			; == 0) goto .endwhile
	inc rax					; index++;
	jmp .while				; goto .while

.endwhile:
	; xor rax, rax
	movzx rax, al
	movzx rbx, bl
	sub rax, rbx 
	ret
