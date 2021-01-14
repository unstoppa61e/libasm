section .text
	global _ft_write
	extern ___error

_ft_write:
	test rdi, rdi		; if (fd
	js .error			;			< 0) goto .error

	test rdx, rdx		; if (count
	jc .error			; 		 < 0) goto .error

	mov rax, 0x2000004  ; func = write;
	syscall             ; ret = func(fd, buf, count)
	; js .error			; if (ret < 0) goto .error
	jc .error			; if (ret < 0) goto .error
	; jb .error			; if (ret < 0) goto .error
	jmp .end			; goto .end

.error:
	push rax
	call ___error
	pop qword[rax]
	; pop rax
	mov rax, -1			; ret = -1;
	jmp .end			; goto .end

.end:
	ret					; return (ret);
