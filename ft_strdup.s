; char    *ft_strdup(const char *s1)
; size_t  ft_strLEN(const char *s);
; char    *ft_strcpy(char *dst, const char *src);

%define ARG1 rdi
%define ARG2 rsi
%define ARG3 rdx
%define LEN  rax

default rel

section .text
    extern _ft_strlen
    extern _ft_strcpy
    extern _malloc
    global _ft_strdup

_ft_strdup:
    push    ARG1            ; var = str;
    call    _ft_strlen      ; LEN = ft_strLEN(str);

    lea     ARG1, [LEN + 1] ; ARG1 = LEN + 1;
    call    _malloc         ; LEN = malloc(ARG1);

    mov     ARG1, rax       ; ARG1 = LEN;
    pop     ARG2            ; ARG2 = var;
    call    _ft_strcpy      ; retV = ft_strcpy(ARG1, ARG2);

    ret                     ; return (retV);
