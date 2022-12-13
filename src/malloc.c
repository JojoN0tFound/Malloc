/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jquivogn <jquivogn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 02:15:18 by jquivogn          #+#    #+#             */
/*   Updated: 2022/12/13 20:54:35 by jquivogn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

t_heap		g_store_mem;

t_block		*new_block(t_chunck *chunck, size_t size)
{
	t_block	*new;

	new = (t_block *)((uint64_t)chunck + CHUNCK_H);
	// ft_putnbr(size);
	// ft_putchar('\n');
	// ft_putnbr(MOD_BASE(size));
	// ft_putchar('\n');
	// print_memory(new, BLOCK_H);
	// ft_putchar('\n');
	while (IS_MAGIC(new->free) && (new->free & USED) == 2)
	{
		YO
		// ft_putstr("=====\n");
		// ft_putnbr(MOD_BASE(new->size)+BLOCK_H);
		// ft_putchar('\n');
		// ft_putnbr(MOD_BASE(((uint64_t)new+8) + BLOCK_H));
		// ft_putchar('\n');
		new += MOD_BASE(new->size) + BLOCK_H;
		// ft_putstr("=====\n");
	}
	new->free = (MAGIC | USED);
	new->size = MOD_BASE(size);
	// ft_putstr("new block=");
	// ft_putchar('\n');
	// print_memory((void *)((uint64_t)new & USED), BLOCK_H);
	// ft_putchar('\n');
	return (new);
}

size_t		get_block_size(size_t size)
{
	if (size > TINY)
		return (SMALL);
	return (TINY);
}

t_block		*get_head(t_chunck **head, size_t size)
{
	t_chunck	*chunck;
	t_block		*block;

	chunck = find_free_chunck(head, size);
	if (chunck)
	{
		chunck->space += MOD_BASE(size + BLOCK_H);
		if((block = new_block(chunck, size))){
			print_memory(block, 16);
			return (block++);
		}
	}
	if (!get_new_chunck(head, size))
		return (NULL);
	return (get_head(head, size));
}

void		*ft_malloc(size_t size)
{
	if (!size)
		return (NULL);
	// if (size > SMALL)
	// 	return(get_new_large_chunck(&g_store_mem.large, size));
	return (get_head(size > TINY ? &g_store_mem.small : &g_store_mem.tiny, size));
}
