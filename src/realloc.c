/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jquivogn <jquivogn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 02:19:08 by jquivogn          #+#    #+#             */
/*   Updated: 2022/12/19 20:28:28 by jquivogn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

void	*get_new_alloc(void *ptr, size_t size)
{
	void	*new;
	void	*tmp;
	t_block	*block;
	size_t	min;

	block = GOTO_H(ptr);
	if (!(new = malloc(size)))
		return (ptr);
	if ((block->magic & FREE) == FREE)
		return (new);
	min = block->size < size ? block->size : size;
	block = NULL;
	tmp = GOTO_M(new);
	tmp = ft_memcpy(tmp, (void *)((uint64_t)ptr), min);
	free(ptr);
	return (tmp);
}

void	*realloc(void *ptr, size_t size)
{
	void	*mem;

	pthread_mutex_lock(&mutex);
	if (!ptr) {
		mem = malloc(size);
		pthread_mutex_unlock(&mutex);
		return (mem);
	}
	if (!size){
		free(ptr);
		pthread_mutex_unlock(&mutex);
		return (NULL);
	}
	mem = get_new_alloc(ptr, size);
	pthread_mutex_unlock(&mutex);
	return (mem);
}
