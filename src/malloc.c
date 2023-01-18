/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jquivogn <jquivogn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 02:15:18 by jquivogn          #+#    #+#             */
/*   Updated: 2023/01/18 20:16:45 by jquivogn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

t_page			*g_first_page = NULL;
pthread_mutex_t	mutex = PTHREAD_MUTEX_INITIALIZER;

int				ite=0;

void		*get_alloc(size_t size)
{
	t_page		*page;
	t_block		*block;

	if ((page = find_free_page(size))){
		if ((block = new_block(page, size))){
			page->fill++;
			if (page->fill == 0)
				print_block(block, -1);
			return (GOTO_M(block));
		}
	}
	P("MALLOC FAIL\n")
	sleep(500);
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