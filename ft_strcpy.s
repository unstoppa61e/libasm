section .text
global _ft_strcpy
_ft_strcpy:
	mov rax, rsi		; ret = src
	cld					; clear the direction flag for movsb

.while:
	cmp byte[rsi], 0	; if (*src - 0
	je .endwhile		;			   == 0) goto .endwhile	
	movsb				; *dst++ = *src++;
	jmp .while			; goto .while

.endwhile:
	mov byte[rdi], 0	; *dst = '\0';
	ret					; return (ret);