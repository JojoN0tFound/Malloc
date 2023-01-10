/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jquivogn <jquivogn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 02:15:18 by jquivogn          #+#    #+#             */
/*   Updated: 2023/01/10 21:03:40 by jquivogn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

t_heap			g_store_mem;
pthread_mutex_t	mutex;
int i = 0;

void		*get_alloc(size_t size)
{
	t_page		*page;
	t_block		*block;

	page = get_head(size);
	if ((page = find_free_page(page, size))){
		if ((block = new_block(page, size))){
			// print_block(block, i++);
			return (GOTO_M(block));
		}
	}
	if ((page = get_new_page(get_head(size), size)))
	{
		if (size > SMALL){
			if ((block = new_block(page, size))){
				return (GOTO_M(block));
			}
		}
		return (get_alloc(size));
	}
	ft_putstr("[MALLOC FAIL]\n");
	return (NULL);
}

void		*malloc(size_t size)
{
	void	*mem;

	pthread_mutex_lock(&mutex);
	// ft_putstr("[START MALLOC]\n");
	if (size == 0){
		ft_putstr("[MALLOC SIZE == 0]\n");
		return (NULL);
	}
	mem = get_alloc(size);
	// ft_putstr("[E--------------------M]\n");
	pthread_mutex_unlock(&mutex);
	return (mem);
}

// void 	*aligned_alloc( size_t alignment, size_t size )
// {
// 	return (malloc(size));
// }
