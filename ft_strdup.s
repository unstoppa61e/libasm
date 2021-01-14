; char		*ft_strdup(const char *s1)
; size_t	ft_strlen(const char *s);
; char		*ft_strcpy(char *dst, const char *src);

%define arg1 rdi
%define arg2 rsi
%define arg3 rdx
%define len rax

default rel

section .text
	extern _ft_strlen
	extern _ft_strcpy
	extern _malloc
	global _ft_strdup

_ft_strdup:
	push arg1					; var = str;
	call _ft_strlen				; len = ft_strlen(str);

	lea arg1, [len + 1]	; arg1 = len + 1;
	call _malloc				; len = malloc(arg1);

	mov arg1, len				; arg1 = len;
	pop arg2					; arg2 = var;
	call _ft_strcpy				; return_str = ft_strcpy(arg1, arg2);

	ret							; return (return_str);
