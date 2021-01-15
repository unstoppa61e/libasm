; ssize_t ft_read(int FD, void *buf, size_t NBYTE);

%define FD          rdi
%define NBYTE       rdx
%define SYSCALL_NUM rax
%define RET_V       rax

section .text
    extern ___error
    global _ft_read

_ft_read:
    test    FD, FD                 ; if (FD
    js      .error                 ;        < 0) goto .error;

    test    NBYTE, NBYTE           ; if (count
    jc      .error                 ;           < 0) goto .error;

    mov     SYSCALL_NUM, 0x2000003 ; func = read;
    syscall                        ; RET_V = func(FD, buf, NBYTE);
    jc      .error                 ; if (RET_V < 0) goto .error;
    jmp     .end                   ; goto .end;

.error:
    push    RET_V                  ; var = RET_V (= errno);
    call    ___error               ; rax = errno memory address
    pop     qword[rax]             ; *(errno memory address) = errno 
    mov     RET_V, -1              ; RET_V = -1;
    jmp     .end                   ; goto .end;

.end:
    ret                            ; return (RET_V);
