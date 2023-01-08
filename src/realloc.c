/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jojo <jojo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 02:19:08 by jquivogn          #+#    #+#             */
/*   Updated: 2023/01/08 20:11:09 by jojo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

void	*get_new_alloc(void *ptr, size_t size)
{
	void	*new;
	t_block	*block;

	block = GOTO_H(ptr);
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
	// ft_putstr("[START REALLOC]\n");
	if (!check_ptr(ptr)){
		pthread_mutex_unlock(&mutex);
		return (malloc(size));
	}
	if (size == 0 && ptr){
		// ft_putstr("[NO SIZE REALLOC]\n");
		pthread_mutex_unlock(&mutex);
		free(ptr);
		return (NULL);
	}
	mem = get_new_alloc(ptr, size);
	// ft_putstr("[E--------------------R]\n");
	pthread_mutex_unlock(&mutex);
	return (mem);
}
