/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jquivogn <jquivogn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 02:19:08 by jquivogn          #+#    #+#             */
/*   Updated: 2023/01/12 15:33:01 by jquivogn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

void	*get_new_alloc(void *ptr, size_t size)
{
	void	*new;
	t_block	*block;

	block = GOTO_H(ptr);
	if (!IS_MAGIC(block->magic)){
		return (NULL);
	}
	// P("size :")
	// ft_putulnbr(size);
	// N
	// P("bsize:")
	// ft_putulnbr(block->size);
	// N
	if (size > block->size){
		if (!(new = get_alloc(size)))
		{
			TEST
			return (ptr);
		}
		new = ft_memcpy(new, ptr, MIN(size, block->size));
		free_block(ptr);
		// print_block(GOTO_H(new), 2);
		return (new);
	}
	// print_block(block, 1);
	return (ptr);
}

void	*realloc(void *ptr, size_t size)
{
	void	*mem;

	mem = NULL;
	pthread_mutex_lock(&mutex);
	if (!check_ptr(ptr))
		mem = get_alloc(size);
	else if (size == 0 && ptr)
		free_block(ptr);
	else 
		mem = get_new_alloc(ptr, size);
	pthread_mutex_unlock(&mutex);
	return (mem);
}
