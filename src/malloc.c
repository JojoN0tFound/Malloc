/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jquivogn <jquivogn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 02:15:18 by jquivogn          #+#    #+#             */
/*   Updated: 2023/01/12 18:26:05 by jquivogn         ###   ########.fr       */
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
		if ((block = new_block(page, size))){
			// print_block(block, i++);
			return (GOTO_M(block));
		}
	P("MALLOC FAIL")
	return (NULL);
}

void		*malloc(size_t size)
{
	void	*mem;

	pthread_mutex_lock(&mutex);
	write(1, "\0", 1);
	// M_S
	if (size == 0)
		mem = NULL;
	else
		mem = get_alloc(size);
	// M_E
	pthread_mutex_unlock(&mutex);
	return (mem);
}
