/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jquivogn <jquivogn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 02:15:18 by jquivogn          #+#    #+#             */
/*   Updated: 2022/12/22 21:08:57 by jquivogn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

t_heap			g_store_mem;
pthread_mutex_t	mutex;

t_block		*get_alloc(t_page **head, size_t size)
{
	t_page		*page;
	t_block		*block;

	if ((page = find_free_page(head, size))){
		block ;
		if ((block = new_block(page, size))){
			page->space -= mod_base(SIZE(size));
			return (GOTO_M(block));
		}
	}
	if (!get_new_page(head, size))
		return (NULL);
	return (get_alloc(head, size));
}

t_block		*get_large_alloc(t_page **head, size_t size)
{
	t_page		*page;

	if (!(page = get_new_page(head, size)))
		return (NULL);
}

// t_block		*get_large_alloc(t_page **head, size_t size)
// {
// 	t_page		*page;
// 	t_block		*new;

// 	YO
// 	if (!(page = get_new_large_page(head, size)))
// 		return (NULL);
// 	DEBUG
// 	new = init_block(ADDR(page) + PAGE_H, size, NULL, NULL);
// 	TOTO
// 	page->space += SIZE(MOD_BASE(size));
// 	page->first = new;
// 	return (GOTO_M(new));
// }

void		*malloc(size_t size)
{
	void	*mem;

	pthread_mutex_lock(&mutex);
	if (size == 0)
		return (NULL);
	// if (size > SMALL)
	// 	mem = get_large_alloc(&g_store_mem.large, size);
	// else
	mem = get_alloc(get_head(size), size);
	pthread_mutex_unlock(&mutex);
	return (mem);
}
