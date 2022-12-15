/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jojo <jojo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 02:40:31 by jquivogn          #+#    #+#             */
/*   Updated: 2022/12/15 00:11:32 by jojo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putstr(char const *s)
{
	while (*s)
		ft_putchar(*s++);
}

int		ft_strlen(char* str)
{
	int	i;

	i = 0;
	while(str[i])
		i++;
	return (i);
}

void	ft_putnbr(int nb)
{
	if (nb < 0)
	{
		ft_putchar('-');
		if (nb == -2147483648) {
			nb = -147483648;
			ft_putchar('2');
		}
		nb *= -1;
	}
	if (nb > 9)
		ft_putnbr(nb / 10);
	ft_putchar((nb % 10) + 48);
}

void print_memory(const void *addr, size_t size)
{
	size_t printed;
	size_t i;
	const unsigned char* pc;
	int g;

	printed = 0;
	i = 0;
	pc = addr;
	while (i < size) {
		g = (*(pc+i) >> 4) & 0xf;
		g += g >= 10 ? 'a'-10 : '0';
		ft_putchar(g);
		printed++;
		g = *(pc+i) & 0xf;
		g += g >= 10 ? 'a'-10 : '0';
		ft_putchar(g);
		printed++;
		if (printed % 32 == 0)
			ft_putchar('\n');
		else if (printed % 4 == 0)
			ft_putchar(' ');
		i++;
	}
}

void	ft_putaddr(unsigned int number)
{
	char ans[8];
	char comp[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C',
			'D', 'E', 'F'};
	int i = 0;

	ft_putstr("0x");
	while (number / 16) {
		ans[i++] = comp[number % 16];
		number /= 16;
	}
	ans[i] = comp[number % 16];
	while (i >= 0) {
		while (ans[i] == 0)
			i--;
		ft_putchar(ans[i--]);
	}
}

void	print_block(t_block *block, int nb)
{
	ft_putstr("=========BLOCK========\n");
	if (nb != -1) {
		ft_putstr("block nb: ");
		ft_putnbr(nb);
		ft_putchar('\n');
	}
	ft_putstr("block addr: ");
	ft_putaddr((uint64_t)block);
	ft_putstr("\nblock magic: ");
	ft_putnbr(block->magic);
	ft_putstr("\nblock size: ");
	ft_putnbr(block->size);
	ft_putstr("\nblock prev: ");
	ft_putaddr((uint64_t)block->prev);
	ft_putstr("\nblock next: ");
	ft_putaddr((uint64_t)block->next);
	ft_putstr("\n======================\n\n");
}

void	print_all_block(t_block *block)
{
	int i = 0;
	while (block) {
		print_block(block, i);
		block = block->next;
		i++;
	}
}