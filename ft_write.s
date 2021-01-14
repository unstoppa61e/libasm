; ssize_t	ft_write(int fildes, const void *buf, size_t nbyte);

%define fd	        rdi
%define buf	    	rsi
%define nbyte   	rdx
%define syscall_num	rax
%define retV        rax

section .text
    global _ft_write
    extern ___error

_ft_write:
    test	fd, fd		   	; if (fd
    js		.error			;        < 0) goto .error

    test	nbyte, nbyte	; if (count
    jc		.error			; 	         < 0) goto .error

    mov		syscall_num, 0x2000004  ; func = write;
    syscall                 ; retV = func(fd, buf, count)
    jc      .error			; if (retV < 0) goto .error
    jmp     .end			; goto .end

.error:
    push     retV           ; var = retV
    call     ___error        
    pop      qword[retV]
    mov      retV, -1		; ret = -1;
    jmp      .end			; goto .end

.end:
    ret			    		; return (ret);
