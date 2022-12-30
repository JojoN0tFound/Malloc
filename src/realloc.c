/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jquivogn <jquivogn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 02:19:08 by jquivogn          #+#    #+#             */
/*   Updated: 2022/12/30 06:25:43 by jquivogn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

void	*get_new_alloc(void *ptr, size_t size)
{
	void	*new;
	t_block	*block;

	block = GOTO_H(ptr);
	if (!IS_MAGIC(block->magic) || (block->magic & FREE) == FREE)
		return (NULL);
	pthread_mutex_unlock(&mutex);
	new = malloc(size);
	pthread_mutex_lock(&mutex);
	if (!new)
		return (ptr);
	new = ft_memcpy(new, ptr, MIN(size, block->size));
	pthread_mutex_unlock(&mutex);
	free(ptr);
	pthread_mutex_lock(&mutex);
	return (new);
}

void	*realloc(void *ptr, size_t size)
{
	void	*mem;

	pthread_mutex_lock(&mutex);
	if (!ptr) {
		pthread_mutex_unlock(&mutex);
		return (malloc(size));
	}
	if (!size){
		pthread_mutex_unlock(&mutex);
		free(ptr);
		return (NULL);
	}
	mem = get_new_alloc(ptr, size);
	pthread_mutex_unlock(&mutex);
	return (mem);
}
