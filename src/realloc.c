/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jquivogn <jquivogn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 02:19:08 by jquivogn          #+#    #+#             */
/*   Updated: 2023/01/18 23:10:48 by jquivogn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

void	*get_new_alloc(void *ptr, size_t size)
{
	t_block	*block = GOTO_H(ptr);
	void	*new;

	if (!IS_MAGIC(block->magic)){
		print_memory((void *)block, 32);
		return (NULL);
	}

	if (mod_base(size) > mod_base(block->size)){
		new = get_alloc(size);

		if (!new){
			print_memory((void *)block, 32);
			return (ptr);
		}

		new = ft_memcpy(new, ptr, block->size);
		if (strncmp(new, ptr, block->size)){
			print_memory((void *)block, 32);
			sleep(500);
		}
		free_block(ptr);

		return (new);
	}

	return (ptr);
}

void	*realloc(void *ptr, size_t size)
{
	void	*mem = NULL;

	pthread_mutex_lock(&mutex);

	R_S
	if (!ptr)
		mem = get_alloc(size);
	else if (size == 0)
		free_block(ptr);
	else
		mem = get_new_alloc(ptr, size);

	R_E
	pthread_mutex_unlock(&mutex);

	return (mem);
}
