#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

void print_memory(const void *addr, size_t size)
{
	size_t printed;
	size_t i;
	const unsigned char* pc;
	int g;

	printed = 0;
	i = 0;
	pc = addr;
	while (i < size){
		g = (*(pc+i) >> 4) & 0xf;
		g += g >= 10 ? 'a'-10 : '0';
		putchar(g);
		printed++;
		g = *(pc+i) & 0xf;
		g += g >= 10 ? 'a'-10 : '0';
		putchar(g);
		printed++;
		if (printed % 32 == 0)
			putchar('\n');
		else if (printed % 4 == 0)
			putchar(' ');
		i++;
	}
}

int main(){

	char *test;

	test = malloc(5);
	test[0] = 't';
	test[1] = 'e';
	test[2] = 's';
	test[3] = 't';
	test[4] = '\0';
	print_memory((void *)((uint64_t)test - 32), 48);
	printf("%s\n", test);
	free(test);
	print_memory((void *)((uint64_t)test - 32), 32);
	printf("%s\n", test);
}