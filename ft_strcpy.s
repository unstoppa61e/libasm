; char    *ft_strcpy(char *dst, const char *src);

section .text
    global _ft_strcpy

_ft_strcpy:
    push    rdi          ; var = dst;
    cld gi                 ; clear the direction flag for movsb

.while:
    cmp     byte[rsi], 0 ; if (*src - '\0'
    je      .endwhile    ;                 == 0) goto .endwhile
    movsb                ; *dst++ = *src++;
    jmp     .while       ; goto .while

.endwhile:
    mov     byte[rdi], 0 ; *dst = '\0';
    pop     rax          ; retV = dst;
    ret                  ; return (retV);
