; void	ft_list_push_front(t_list **begin_list, void *data)

%define type_size		8				; #define LIST_SIZE (= sizeof(t_list)) 8
%define size_per_list	16		; #define SIZE_PER_LIST (= sizeof(t_list *)) 16 
%define arg1			rdi
%define arg2			rsi
%define retV			rax

section .text
	extern _malloc
	global _ft_list_push_front

_ft_list_push_front:
	test	arg1, arg1
	jz		.end
	test	arg2, arg2
	jz		.end

	push	arg1				; var1 = begin_list;
	push	arg2				; var2 = data;

	mov		arg1, size_per_list	; arg1 = 16;
	call	_malloc				; str = malloc(16);

	pop		arg2				; data = var2;
	pop		arg1				; begin_list = var1;

	test	retV, retV 			; if (str
	jz		.end				;			== NULL) goto .end

	mov		[retV], arg2		; str = data;
	mov		rbx, [arg1]			; rbx = *begin_list
	mov		[retV + type_size], rbx;[retV + 8] = rbx;
	mov		[arg1], retV		; *begin_list = 

.end
	ret

; section .text
; 	extern _malloc
; 	global _ft_list_push_front

; _ft_list_push_front:
; 	push	rdi			; store list_start
; 	push	rsi			; store data
; 	mov		rdi, 16		; 1st = 16
; 	call	_malloc		; malloc(16)
; 	pop		rsi			;
; 	pop		rdi			;
; 	cmp		rax, 0		; if ret == NULL
; 	je		end			; then return
; 	mov		[rax], rsi	; lst = data
; 	mov		rcx, [rdi]	;
; 	mov		[rax+8], rcx; lst->next = list_start
; 	mov		[rdi], rax	; list_start = lst

; end:
; 	ret