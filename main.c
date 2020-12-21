int main()
{
	int	a;
	int	b;
	int	c;
	b = 1;
	c = 2;
	_asm{
		mov eax, b
		add eax, c
		mov a, eax}
}
