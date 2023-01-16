/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jojo <jojo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 02:19:08 by jquivogn          #+#    #+#             */
/*   Updated: 2023/01/16 17:28:08 by jojo             ###   ########.fr       */
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
		pthread_mutex_unlock(&mutex);
		new = malloc(size);
		pthread_mutex_lock(&mutex);
		if (!new)
			return (ptr);
		new = ft_memcpy(new, ptr, block->size);
		pthread_mutex_unlock(&mutex);
		free(ptr);
		pthread_mutex_lock(&mutex);
		return (new);
	}
	return (ptr);
}

void	*realloc(void *ptr, size_t size)
{
	void	*mem = NULL;

	pthread_mutex_lock(&mutex);
	// R_S
	if (!ptr){
		pthread_mutex_unlock(&mutex);
		mem = malloc(size);
		pthread_mutex_lock(&mutex);
	}
	else if (size == 0){
		pthread_mutex_unlock(&mutex);
		free(ptr);
		pthread_mutex_lock(&mutex);
	}
	else
		mem = get_new_alloc(ptr, size);
	// R_E
	pthread_mutex_unlock(&mutex);
	return (mem);
}
