/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jquivogn <jquivogn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 02:15:18 by jquivogn          #+#    #+#             */
/*   Updated: 2022/12/10 10:22:49 by jquivogn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

t_memory		g_store_mem;

//• First align the requested size;
//• If base is initialized:
//	– Search for a free chunk wide enough;
//	– If we found a chunk:
//		* Try to split the block (the difference between the requested size and the size of
//		the block is enough to store the meta-data and a minimal block (4 bytes;)
//		* Mark the chunk as used (b->free=0;)
//	– Otherwise: we extend the heap.
//	Note the use of the last: find block put the pointer to the last visited chunk in
//	last, so we can access it during the extension without traversing the whole list
//	again.
//• Otherwise: we extended the heap (which is empty at that point.)

t_block		*find_free_block(t_block **head, size_t size)
{
	t_block	*tmp;

	tmp = *head;
	while (tmp && (tmp->free == USED && tmp->size < size))
		tmp = tmp->next;
	return (tmp);
}

int			split_block(t_block **block, size_t size)
{
	t_block n_block;
	t_block *tmp;

	tmp = *block;
	if (tmp && tmp->size < size + BLOCK_SIZE)
		return (FALSE);
	n_block.size = size;
	n_block.next = tmp;
	n_block.prev = tmp->prev;
	n_block.free = USED;
	tmp->prev = &n_block;
	tmp->size -= size;
	return (TRUE);
}

size_t		get_new_block_size(size_t size)
{
	size_t	b_size;

	if (size > SMALL)
		b_size = ((size + BLOCK_SIZE) / getpagesize() + 1) * getpagesize();
	else
		b_size = ((((size > TINY ? SMALL : TINY) + BLOCK_SIZE) * 100) / getpagesize() + 1) * getpagesize();
	return (b_size);
}

void		add_new_to_memory(t_block **head, t_block *new)
{
	t_block	*tmp;

	tmp = *head;
	if (!tmp)
	{
		*head = new;
		return ;
	}
	while(tmp && tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	new->prev = tmp;
}

t_block		*extend_heap(t_block **head, size_t size)
{
	t_block	*new;
	size_t	block_size;

	block_size = get_new_block_size(size);
	new = (t_block *)mmap(NULL, block_size,
		PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
	if (!new)
		return (NULL);
	new->size = block_size;
	new->free = FREE;
	add_new_to_memory(head, new);
	return (new);
}

t_block		*get_head(size_t size)
{
	t_block	*head;
	t_block	*block;

	head = (size > TINY ? g_store_mem.small : g_store_mem.tiny);
	block = find_free_block(&head, size);
	if (split_block(&block, size))
		return (block);
	return (extend_heap(&head, size));
}

void		*malloc(size_t size)
{
	if (!size || size > ULONG_MAX)
		return (NULL);
	if (size > SMALL)
	{
		return(extend_heap(&g_store_mem.large, size));
	}
	return (get_head(size));
}
