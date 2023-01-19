/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jojo <jojo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 02:15:18 by jquivogn          #+#    #+#             */
/*   Updated: 2023/01/19 17:32:13 by jojo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

t_page			*g_first_page = NULL;
pthread_mutex_t	mutex = PTHREAD_MUTEX_INITIALIZER;

void		*get_alloc(size_t size)
{
	t_page		*page;
	t_block		*block = NULL;
	size_t		mod_size = mod_base(size);

	if ((page = find_free_page(&block, size))){

		if (page->type == L)
			return (GOTO_M(FIRST(page)));

		if (block)
			block = split_block(block, mod_size);
		else
			block = split_block(FIRST(page), mod_size);

		page->fill -= (block->size + BLOCK_H);
		block->size = size;

		return (GOTO_M(block));
	}
	return (NULL);
}

void		*malloc(size_t size)
{
	void	*mem;

	pthread_mutex_lock(&mutex);

	if (size == 0)
		size = 1;

	mem = get_alloc(size);

	pthread_mutex_unlock(&mutex);

	return (mem);
}