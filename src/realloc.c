/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jquivogn <jquivogn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 02:19:08 by jquivogn          #+#    #+#             */
/*   Updated: 2023/01/11 19:29:44 by jquivogn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

void	*get_new_alloc(void *ptr, size_t size)
{
	void	*new;
	t_block	*block;

	block = GOTO_H(ptr);
	new = get_alloc(size);
	if (!new)
		return (ptr);
	new = ft_memcpy(new, ptr, MIN(size, block->size));
	free_block(ptr);
	return (new);
}

void	*realloc(void *ptr, size_t size)
{
	void	*mem;

	pthread_mutex_lock(&mutex);
	// ft_putstr("[START REALLOC]\n");
	if (!check_ptr(ptr)){
		// P("[ERROR: no ptr realloc]\n");
		mem = get_alloc(size);
	}
	else if (size == 0 && ptr){
		// ft_putstr("[NO SIZE REALLOC]\n");
		free_block(ptr);
		mem = NULL;
	}
	else 
		mem = get_new_alloc(ptr, size);
	// ft_putstr("[E--------------------R]\n");
	pthread_mutex_unlock(&mutex);
	return (mem);
}
