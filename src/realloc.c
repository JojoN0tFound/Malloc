/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jquivogn <jquivogn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 02:19:08 by jquivogn          #+#    #+#             */
/*   Updated: 2023/01/12 18:22:43 by jquivogn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

void	*get_new_alloc(void *ptr, size_t size)
{
	void	*new;
	t_block	*block;

	block = GOTO_H(ptr);
	if (!IS_MAGIC(block->magic))
		return (NULL);
	if (mod_base(size) > mod_base(block->size)){
		if (!(new = get_alloc(size)))
			return (ptr);
		new = ft_memcpy(new, ptr, block->size);
		free_block(ptr);
		return (new);
	}
	return (ptr);
}

void	*realloc(void *ptr, size_t size)
{
	void	*mem;

	mem = NULL;
	pthread_mutex_lock(&mutex);
	// R_S
	if (!ptr)
		mem = get_alloc(size);
	else if (size == 0)
		free_block(ptr);
	else 
		mem = get_new_alloc(ptr, size);
	// R_E
	pthread_mutex_unlock(&mutex);
	return (mem);
}
