; void ft_list_push_front(t_list **BEGIN_LIST, void *DATA)

; typedef struct      s_list
; {
;     void            *DATA;
;     struct s_list   *next;
; }                   t_list;

MEMBER_SIZE equ 8  ; (= sizeof(void *)) 
LIST_SIZE   equ 16 ; (= sizeof(t_list)) 

%define ARG        rdi
%define BEGIN_LIST rdi
%define DATA       rsi
%define LST        rax
%define LIST_HEAD  r8

section .text
    extern _malloc
    global _ft_list_push_front

_ft_list_push_front:
    test    BEGIN_LIST, BEGIN_LIST         ; if (BEGIN_LIST == NULL)
    jz      .end                           ;     goto .end;

    test    DATA, DATA                     ; if (DATA == NULL)
    jz      .end                           ;     goto .end;

    push    BEGIN_LIST                     ; var1 = BEGIN_LIST;
    push    DATA                           ; var2 = DATA;

    mov     ARG, LIST_SIZE                 ; BEGIN_LIST = 16;
    call    _malloc                        ; t_list LST = malloc(16);

    pop     DATA                           ; DATA = var2;
    pop     BEGIN_LIST                     ; BEGIN_LIST = var1;

    test    LST, LST                       ; if (LST
    jz      .end                           ;         == NULL) goto .end;

    mov     [LST], DATA                    ; LST->DATA = DATA;
    mov     LIST_HEAD, [BEGIN_LIST]        ; LIST_HEAD = *BEGIN_LIST; (= 1st list)
    mov     [LST + MEMBER_SIZE], LIST_HEAD ; LST->next = LIST_HEAD;
    mov     [BEGIN_LIST], LST              ; *BEGIN_LIST = LST;

.end:
    ret
