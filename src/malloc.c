/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jquivogn <jquivogn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 02:15:18 by jquivogn          #+#    #+#             */
/*   Updated: 2023/01/09 16:53:34 by jquivogn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

t_heap			g_store_mem;
pthread_mutex_t	mutex;

void		*get_alloc(t_page **head, size_t size)
{
	t_page		*page;
	t_block		*block;

	if ((page = find_free_page(head, size))){
		if ((block = new_block(page, size))){
			return (GOTO_M(block));
		}
	}
	if ((page = get_new_page(head, size)))
		return (get_alloc(head, size));
	ft_putstr("[MALLOC FAIL]\n");
	return (NULL);
}

// void		*get_large_alloc(t_page **head, size_t size)
// {
// 	t_page		*page;
// 	t_block		*block;

// 	if (!(page = get_new_page(head, size)))
// 		return (NULL);
// 	if (!(block = new_block(page, size)))
// 		return (NULL);
// 	return (GOTO_M(block));
// }

void		*malloc(size_t size)
{
	void	*mem;

	pthread_mutex_lock(&mutex);
	// ft_putstr("[START MALLOC]\n");
	if (size == 0){
		ft_putstr("[MALLOC SIZE == 0]\n");
		return (NULL);
	}
	mem = get_alloc(get_head(size), size);
	// ft_putstr("[E--------------------M]\n");
	pthread_mutex_unlock(&mutex);
	return (mem);
}
