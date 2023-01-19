/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jojo <jojo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 20:55:01 by jquivogn          #+#    #+#             */
/*   Updated: 2023/01/19 22:20:00 by jojo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

void	ft_print_memory(const void *addr, size_t size)
{
	int		printed = 0;
	size_t	i = 0;
	int		c;
	const unsigned char*	pc = addr;

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
}

void	print_block(t_block *block, int nb)
{
	ft_putstr("=========== BLOCK ==========\n");
	if (nb != -1){
		ft_putstr("block nb: ");
		ft_putnbr(nb);
		ft_putchar('\n');
	}
	ft_putstr("block addr: ");
	ft_putaddr((uint64_t)block);
	ft_putstr("\ndata  addr: ");
	ft_putaddr((uint64_t)block + BLOCK_H);
	ft_putstr("\naddr magic: ");
	ft_putaddr(block->magic);
	ft_putstr("\nblock size: ");
	ft_putulnbr(block->size);
	ft_putstr("\nblock prev: ");
	ft_putaddr((uint64_t)block->prev);
	ft_putstr("\nblock next: ");
	ft_putaddr((uint64_t)block->next);
	ft_putstr("\n============================\n");
}

void	print_all_block(t_block *block)
{
	int i = 0;

	while(block->prev)
		block = block->prev;

	while (block){
		print_block(block, i++);
		block = block->next;
	}
}