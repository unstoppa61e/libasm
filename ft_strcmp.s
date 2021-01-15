; int ft_strcmp(const char *s1, const char *s2);

%macro CLEAR_REG 1
    xor %1, %1
%endmacro

section .text
    global _ft_strcmp

_ft_strcmp:
    CLEAR_REG rax              ; c1 = 0;
    CLEAR_REG rcx              ; c2 = 0;
    CLEAR_REG r8               ; index = 0;

.while:
    mov     al, byte[rdi + r8] ; c1 = s1[index];
    mov     cl, byte[rsi + r8] ; c2 = s2[index];

    cmp     al, 0              ; if (c1 - 0
    je      .endwhile          ;            == 0) goto .endwhile

    cmp     al, cl             ; if (c1 - c2
    jne     .endwhile          ;             != 0) goto .endwhile

    inc     r8                 ; index++;
    jmp     .while             ; goto .while

.endwhile:
    sub     rax, rcx           ; c1 -= c2;
    ret                        ; return (c1);
