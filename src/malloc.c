/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jojo <jojo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 02:15:18 by jquivogn          #+#    #+#             */
/*   Updated: 2022/12/15 01:52:23 by jojo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

t_heap		g_store_mem;

t_block		*get_alloc(t_page **head, size_t size)
{
	t_page		*page;
	t_block		*block;

	page = find_free_page(head, size);
	if (page) {
		if((block = new_block(page, size))) {
			page->space += SIZE(MOD_BASE(size));
			return (block);
		}
		return (get_alloc(head, size));
	}
	if (!get_new_page(head, size))
		return (NULL);
	return (get_alloc(head, size));
}

t_block		*get_large_alloc(t_page **head, size_t size)
{
	t_page		*page;
	t_block		*new;

	if (!(page = get_new_large_page(head, size)))
		return (NULL);
	new = init_block((uint64_t)page + PAGE_H, size, NULL, NULL);
	page->space += SIZE(MOD_BASE(size));
	return (new);
	
}

void		*malloc(size_t size)
{
	if (!size)
		return (NULL);
	if (size > SMALL)
		return(get_large_alloc(&g_store_mem.large, size));
	return (get_alloc(size > TINY ? &g_store_mem.small : &g_store_mem.tiny, size));
}
