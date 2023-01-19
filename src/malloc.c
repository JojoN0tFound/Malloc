/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jojo <jojo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 02:15:18 by jquivogn          #+#    #+#             */
/*   Updated: 2023/01/19 15:25:21 by jojo             ###   ########.fr       */
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

		if (page->type == L)
			return (GOTO_M(FIRST(page)));

		if ((block = new_block(page, mod_base(size)))){
			page->fill++;
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

	// M_S
	if (size == 0)
		size = 1;

	mem = get_alloc(size);

	// M_E
	pthread_mutex_unlock(&mutex);

	return (mem);
}