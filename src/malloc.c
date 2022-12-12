// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   malloc.c                                           :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: jquivogn <jquivogn@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2022/12/10 02:15:18 by jquivogn          #+#    #+#             */
// /*   Updated: 2022/12/12 20:25:34 by jquivogn         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "../includes/malloc.h"

// t_heap		g_store_mem;

// t_block		*find_free_block(t_block **head, size_t size)
// {
// 	t_block	*tmp;

// 	tmp = *head;
// 	while (tmp && tmp->next && (tmp->free == USED || tmp->size < size + BLOCK_SIZE))
// 	{
// 		tmp = tmp->next;
// 	}
// 	if (tmp && tmp->next == NULL && (tmp->free == USED || tmp->size < size + BLOCK_SIZE))
// 		return (NULL);
// 	return (tmp);
// }

// int			split_block(t_block **block, t_block **remaining, size_t size)
// {
// 	t_block	*left;
// 	t_block *tmp;

// 	tmp = *block;
// 	left = *remaining;
// 	if (tmp && (tmp->free == USED || tmp->size < size + BLOCK_SIZE))
// 		return (FALSE);
// 	left->size = tmp->size - size;
// 	left->free = FREE;
// 	left->next = NULL;
// 	tmp->free = USED;
// 	tmp->size = size;
// 	tmp->next = left;
// 	return (TRUE);
// }

// size_t		get_head_size(size_t size)
// {
// 	if (size > TINY)
// 		return (SMALL);
// 	return (TINY);
// }

// void		add_new_to_memory(t_block **head, t_block *new)
// {
// 	t_block	*tmp;

// 	tmp = *head;
// 	if (!tmp)
// 	{
// 		*head = new;
// 		return ;
// 	}
// 	while(tmp && tmp->next)
// 	{
// 		tmp = tmp->next;
// 	}
// 	tmp->next = new;
// }

// int			extend_heap(t_block **head, size_t size)
// {
// 	t_block	*new;
// 	size_t	block_size;

// 	block_size = ((get_head_size(size) * 100) / (getpagesize() + 1)) * getpagesize();
// 	new = (t_block *)mmap(NULL, block_size,
// 		PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
// 	if (!new)
// 		return (FALSE);
// 	new->size = block_size;
// 	new->free = FREE;
// 	new->next = NULL;
// 	add_new_to_memory(head, new);
// 	return (TRUE);
// }

// t_block		*extend_large_heap(t_block **head, size_t size)
// {
// 	t_block	*new;
// 	size_t	block_size;

// 	block_size = size + BLOCK_SIZE;
// 	new = (t_block *)mmap(NULL, block_size,
// 		PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
// 	if (!new)
// 		return (NULL);
// 	new->size = block_size;
// 	new->free = USED;
// 	new->next = NULL;
// 	add_new_to_memory(head, new);
// 	return (new);
// }

// t_block		*get_head(t_block **head, size_t size)
// {
// 	t_block	*block;
// 	t_block	*remaining;

// 	block = find_free_block(head, size);
// 	if (block && block->free == FREE)
// 	{
// 		if(split_block(&block, &remaining, size))
// 		{
// 			return (block);
// 		}
// 		return (NULL);
// 	}
// 	if (!extend_heap(head, size))
// 		return (NULL);
// 	return (get_head(head, size));
// }

// void		*ft_malloc(size_t size)
// {
// 	t_block	*block;

// 	if (!size)
// 		return (NULL);
// 	if (size > SMALL)
// 		return(extend_large_heap(&g_store_mem.large, size) + BLOCK_SIZE);
// 	block = get_head(size > TINY ? &g_store_mem.small : &g_store_mem.tiny, size);
// 	return (block);
// }
