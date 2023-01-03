/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jojo <jojo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 02:15:18 by jquivogn          #+#    #+#             */
/*   Updated: 2023/01/02 17:11:26 by jojo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

t_heap			g_store_mem;
pthread_mutex_t	mutex;

void		*get_alloc(t_page **head, size_t size)
{
	t_page		*page;
	t_block		*block;

	if ((page = find_free_page(head, size)))
		if ((block = new_block(page, size)))
			return (GOTO_M(block));
	if ((page = get_new_page(head, size)))
		return (get_alloc(head, size));
	return (NULL);
}

void		*get_large_alloc(t_page **head, size_t size)
{
	t_page		*page;
	t_block		*block;

	if (!(page = get_new_page(head, size)))
		return (NULL);
	if (!(block = new_block(page, size)))
		return (NULL);
	return (GOTO_M(block));
}

void		*malloc(size_t size)
{
	void	*mem;

	pthread_mutex_lock(&mutex);
	ft_putstr("[S M]\n");
	if (size == 0)
		return (NULL);
	if (size > SMALL)
		mem = get_large_alloc(&g_store_mem.large, size);
	else
		mem = get_alloc(get_head(size), size);
	if (mem == NULL){
		// ft_putstr("[EFM]\n");
	}
	ft_putstr("[E M]\n");
	pthread_mutex_unlock(&mutex);
	return (mem);
}
