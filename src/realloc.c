/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jquivogn <jquivogn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 02:19:08 by jquivogn          #+#    #+#             */
/*   Updated: 2022/12/17 12:34:35 by jquivogn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

void	*get_new_alloc(void *ptr, size_t size)
{
	void	*new;
	void	*tmp;
	t_block	*block;
	size_t	min;

	COUCOU
	new = malloc(size);
	TOTO
	if (!new)
		return (ptr);
	SEGV
	block = GOTO_H(ptr);
	SEGV
	min = block->size < size ? block->size : size;
	block = NULL;
	tmp = GOTO_M(new);
	tmp = ft_memcpy(tmp, (void *)((uint64_t)ptr + BLOCK_H), min);
	free(ptr);
	// show_alloc_mem();
	return (new);
}

void	*realloc(void *ptr, size_t size)
{
	if (!ptr)
		return (malloc(size));
	if (!size){
		free(ptr);
		return (NULL);
	}
	return (get_new_alloc(ptr, size));
}