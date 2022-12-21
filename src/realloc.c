/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jquivogn <jquivogn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 02:19:08 by jquivogn          #+#    #+#             */
/*   Updated: 2022/12/21 15:04:41 by jquivogn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

void	*get_new_alloc(void *ptr, size_t size)
{
	void	*new;
	void	*tmp;
	t_block	*block;
	size_t	min;

	BRUH
	block = GOTO_H(ptr);
	pthread_mutex_unlock(&mutex);
	new = malloc(size);
	print_block(new, 2);
	pthread_mutex_lock(&mutex);
	if (!new)
		return (ptr);
	if ((block->magic & FREE) == FREE)
		return (new);
	min = block->size < size ? block->size : size;
	block = NULL;
	tmp = GOTO_M(new);
	tmp = ft_memcpy(tmp, (void *)(ADDR(ptr)), min);
	pthread_mutex_unlock(&mutex);
	free(ptr);
	pthread_mutex_lock(&mutex);
	return (tmp);
}

void	*realloc(void *ptr, size_t size)
{
	void	*mem;

	pthread_mutex_lock(&mutex);
	if (!ptr) {
		pthread_mutex_unlock(&mutex);
		mem = malloc(size);
		return (mem);
	}
	if (!size){
		pthread_mutex_unlock(&mutex);
		free(ptr);
		return (NULL);
	}
	mem = get_new_alloc(ptr, size);
	print_block(GOTO_H(mem), 1);
	pthread_mutex_unlock(&mutex);
	return (mem);
}
