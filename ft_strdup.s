; char		*ft_strdup(const char *s1)
; size_t	ft_strlen(const char *s);
; char		*ft_strcpy(char *dst, const char *src);

%define arg1 rdi
%define arg2 rsi
%define arg3 rdx
%define retV rax

section .text
	extern _ft_strlen
	extern _ft_strcpy
	extern _malloc
	global _ft_strdup

_ft_strdup:
	push arg1					; var = str;
	call _ft_strlen				; retV = ft_strlen(str);

	lea arg1, [rel retV + 1]	; arg1 = retV + 1;
	call _malloc				; retV = malloc(arg1);

	mov arg1, retV				; arg1 = retV;
	pop arg2					; arg2 = var;
	call _ft_strcpy				; retV = ft_strcpy(arg1, arg2);

	ret							; return (retV);
