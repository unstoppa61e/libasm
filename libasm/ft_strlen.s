; size_t ft_strlen(const char *S);

%define INDEX rax
%define S     rdi

section .text
    global _ft_strlen

_ft_strlen:
    xor     INDEX, INDEX       ; INDEX = 0;

.while:
    cmp     byte[S + INDEX], 0 ; if (S[INDEX] - '\0'
    je      .endwhile          ;                     == 0) goto .endwhile
    inc     INDEX              ; INDEX++;
    jmp     .while             ; goto .while;

.endwhile:
    ret                        ; return (INDEX);
