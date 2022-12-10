/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jquivogn <jquivogn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 02:15:18 by jquivogn          #+#    #+#             */
/*   Updated: 2022/12/10 07:36:12 by jquivogn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"


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

t_block	*find_free_block(t_block **head, size_t size)
{
	t_block	*tmp;

	tmp = *head;
	while (tmp && (tmp->free == USED && tmp->size < size))
		tmp = tmp->next;
	return (tmp);
}

int		split_block(t_block *block, size_t size)
{
	t_block *n_block;

	if (block->size < size + BLOCK_SIZE)
		return (FALSE);
	n_block->size = size;
	n_block->next = block;
	n_block->prev = block->prev;
	n_block->free = USED;
	block->prev = n_block;
	block->size -= size;
}

size_t	get_new_page_size(size_t size)
{
	if (size <= TINY)
		return (TINY);
	else
		return (SMALL);
}

void	add_new_to_memory(t_block **head, t_block *new)
{
	t_block	*tmp;

	tmp = *head;
	while(tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	new->prev = tmp;
}

t_block	*extend_heap(t_block **head, size_t size)
{
	t_block	*new;
	size_t	page_size;
	size_t	block_size;

	page_size = get_new_page_size(size) + BLOCK_SIZE;
	block_size = sizeof(t_block) + 100 * page_size;
	block_size = (block_size / getpagesize() + 1) * getpagesize();
	new = (t_block *)mmap(NULL, block_size,
		PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
	if (!new)
		return (NULL);
	new->size = block_size;
	new->free = FREE;
	add_new_to_memory(head, new);
	return (new);
}

void	*malloc(size_t size)
{
	if (!size || size > ULONG_MAX)
		return (NULL);
	if (size > SMALL)
	{
		//increase heap size
	}
	return (NULL);
}
