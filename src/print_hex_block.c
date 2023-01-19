
#include "../includes/malloc.h"

int		print_memory(const void *addr, size_t size, int printed, char *color)
{
	size_t i = 0;
	const unsigned char* pc = addr;
	int c;

	P(color)
	while (i < size){
		c = (*(pc+i) >> 4) & 0xf;
		c += c >= 10 ? 'a'-10 : '0';

		ft_putchar(c);
		printed++;

		c = *(pc+i) & 0xf;
		c += c >= 10 ? 'a'-10 : '0';

		ft_putchar(c);
		printed++;

		if (printed % 32 == 0)
			ft_putchar('\n');
		else if (printed % 4 == 0)
			ft_putchar(' ');

		i++;
	}
	P(WHI)

	return (printed);
}

void	print_hex_block(void *ptr)
{
	t_block	*block = GOTO_H(ptr);
	int		printed = 0;
	t_page	*page;

	if (!(page = find_block_page(ADDR(block))) || !IS_MAGIC(block->magic)){
		ft_putstr("[NOT A VALID POINTER]\n");
		return ;
	}

	pthread_mutex_lock(&mutex);
	
	P(BLU)
	ft_putstr("BLOCK HEADER: ");
	ft_putaddr(ADDR(block));
	ft_putstr("\n");
	printed = print_memory(block, 8, printed, ORA);
	printed = print_memory((void *)(ADDR(block) + 8), 8, printed, GRN);
	printed = print_memory((void *)(ADDR(block) + 16), 8, printed, DRK);
	print_memory((void *)(ADDR(block) + 24), 8, printed, PUR);
	
	P(CYA)
	ft_putstr("BLOCK MEMORY: ");
	ft_putaddr(ADDR(ptr));
	ft_putstr("\n");
	printed = 0;
	printed = print_memory(ptr, block->size, printed, WHI);
	
	if (block->size % 16 != 0)
		print_memory((ptr + block->size), 16 - (block->size % 16), printed, RED);
	ft_putstr("\n\n");

	pthread_mutex_unlock(&mutex);
}