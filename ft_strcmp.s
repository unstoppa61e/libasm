; int		ft_strcmp(const char *s1, const char *s2);

%macro clear_reg 1
	xor %1, %1
%endmacro

section .text
	global _ft_strcmp

_ft_strcmp:
	clear_reg rax			; c1 = 0;
	clear_reg rbx			; c2 = 0;
	clear_reg r8			; index = 0;

.while:
	mov al, byte[rdi + r8]	; c1 = s1[index];
	mov bl, byte[rsi + r8]	; c2 = s2[index];
	cmp al, 0				; if (c1 - 0
	je .endwhile			; 			  == 0) goto .endwhile
	cmp al, 0				; if (c2 - 0
	je .endwhile			; 			  == 0) goto .endwhile
	cmp al, bl				; if (c1 - c2
	jne .endwhile			;			  != 0) goto .endwhile
	inc r8					; index++;
	jmp .while				; goto .while

.endwhile:
	sub rax, rbx			; c1 -= c2;
	ret						; return (c1);
