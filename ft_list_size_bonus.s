%define type_size 8				; #define TYPE_SIZE (= sizeof(t_list)) 8

section .text
	global _ft_list_size

_ft_list_size:
	xor rax, rax				; count = 0;

.while
	test rdi, rdi				; if (rdi == 0)
	jz .endwhile				;	goto .endwhile

	mov rdi, [rdi + type_size]	; list = list->next
	inc rax						; count++;
	jmp .while					; goto .while

.endwhile
	ret							; return (count);