/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jojo <jojo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 02:15:18 by jquivogn          #+#    #+#             */
/*   Updated: 2023/01/15 23:49:29 by jojo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

t_page			*g_first_page = NULL;
pthread_mutex_t	mutex = PTHREAD_MUTEX_INITIALIZER;
int				i=0;

void		*get_alloc(size_t size)
{
	t_page		*page;
	t_block		*block;

	if ((page = find_free_page(size)))
		if ((block = new_block(page, size)))
			return (GOTO_M(block));
	P("MALLOC FAIL\n")
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
	pthread_mutex_unlock(&mutex);
	return (mem);
}

	// if ((uint64_t)mem >> 40 != 127){
	// 	ft_putaddr(ADDR(mem));
	// 	N
	// }