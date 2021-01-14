; int ft_list_size(t_list *begin_list);

; typedef struct	s_list
; {
; 	void			*data;
; 	struct s_list	*next;
; }					t_list;

%define MEMBER_SIZE 8      ; (sizeof(void *))
%define count		rax                 
%define begin_list	rdi

section .text
    global _ft_list_size

_ft_list_size:
    xor		count, count				; count = 0;

.while:
    test	begin_list, begin_list		; if (begin_list == NULL)
    jz		.endwhile					; 	goto .endwhile

    mov		begin_list, [begin_list + MEMBER_SIZE]	; begin_list = begin_list->next
    inc		count						; count++;
    jmp		.while						; goto .while

.endwhile
    ret									; return (count);