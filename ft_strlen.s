; size_t	ft_strlen(const char *s);

%define index rax
%define s	  rdi

section .text
    global _ft_strlen

_ft_strlen:
    xor index, index; index = 0;

.while:
    cmp	byte[s + rax], 0	; if (str[index] - 0
    je	.endwhile			; 					 == 0) goto .endwhile
    inc index				; index++;
    jmp .while				; goto .while

.endwhile:
    ret						; return (index);