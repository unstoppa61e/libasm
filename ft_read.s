; ssize_t	ft_read(int fildes, void *buf, size_t nbyte);

section .text
	global _ft_read

_ft_read:
	test rdi, rdi		; if (fd
	js .error			;			< 0) goto .error

	test rdx, rdx		; if (count
	jc .error			; 		 < 0) goto .error

	mov rax, 0x2000003  ; func = read;
	syscall             ; ret = func(fd, buf, count)
	js .error			; if (ret < 0) goto .error
	jmp .end			; goto .end

.error:
	mov rax, -1			; ret = -1;
	jmp .end			; goto .end

.end:
	ret					; return (ret);
