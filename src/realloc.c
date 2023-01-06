/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jquivogn <jquivogn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 02:19:08 by jquivogn          #+#    #+#             */
/*   Updated: 2023/01/06 14:51:40 by jquivogn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

void	*get_new_alloc(void *ptr, size_t size)
{
	void	*new;
	t_block	*block;

	block = GOTO_H(ptr);
	if (!IS_MAGIC(block->magic) || (block->magic & FREE) == FREE){
		ft_putstr("[NO PTR REALLOC]\n");
		return (NULL);
	}
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
	ft_putstr("[START REALLOC]\n");
	if (!ptr) {
		ft_putstr("[NO PTR REALLOC]\n");
		pthread_mutex_unlock(&mutex);
		return (malloc(size));
	}
	if (!size && ptr){
		ft_putstr("[NO SIZE REALLOC]\n");
		pthread_mutex_unlock(&mutex);
		free(ptr);
		return (NULL);
	}
	mem = get_new_alloc(ptr, size);
	ft_putstr("[E--------------------R]\n");
	pthread_mutex_unlock(&mutex);
	return (mem);
}
