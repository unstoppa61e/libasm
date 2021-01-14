; void	ft_list_push_front(t_list **begin_list, void *data)

; typedef struct	s_list
; {
; 	void			*data;
; 	struct s_list	*next;
; }					t_list;

%define MEMBER_SIZE		8		; (= sizeof(void *)) 
%define LIST_SIZE		16		; (= sizeof(t_list)) 
%define arg				rdi
%define begin_list		rdi
%define data			rsi
%define lst				rax
%define list_head		rbx

section .text
    extern _malloc
    global _ft_list_push_front

_ft_list_push_front:
    test	begin_list, begin_list
    jz		.end

    test	data, data
    jz		.end

    push	begin_list			; var1 = begin_list;
    push	data				; var2 = data;

    mov		arg, LIST_SIZE		; begin_list = 16;
    call	_malloc				; t_list lst = malloc(16);

    pop		data				; data = var2;
    pop		begin_list			; begin_list = var1;

    test	lst, lst 			; if (lst
    jz		.end				;			== NULL) goto .end

    mov		[lst], data						; lst->data = data;
    mov		list_head, [begin_list]			; list_head = *begin_list (= 1st list)
    mov		[lst + MEMBER_SIZE], list_head	; lst->next = list_head;
    mov		[begin_list], lst				; *begin_list = lst

.end
    ret