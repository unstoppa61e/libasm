; int ft_list_size(t_list *BEGIN_LIST);

; typedef struct      s_list
; {
;     void            *data;
;     struct s_list   *next;
; }                   t_list;

MEMBER_SIZE     equ 8 ; (sizeof(void *))

%define COUNT       rax                 
%define BEGIN_LIST  rdi

section .text
    global _ft_list_size

_ft_list_size:
    xor     COUNT, COUNT                           ; COUNT = 0;

.while:
    test    BEGIN_LIST, BEGIN_LIST                 ; if (BEGIN_LIST == NULL)
    jz      .endwhile                              ;     goto .endwhile;

    mov     BEGIN_LIST, [BEGIN_LIST + MEMBER_SIZE] ; BEGIN_LIST = BEGIN_LIST->next;
    inc     COUNT                                  ; COUNT++;
    jmp     .while                                 ; goto .while;

.endwhile:
    ret                                            ; return (COUNT);
