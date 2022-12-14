/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jojo <jojo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 02:15:18 by jquivogn          #+#    #+#             */
/*   Updated: 2022/12/14 17:57:12 by jojo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

t_heap		g_store_mem;

t_block		*get_head(t_page **head, size_t size)
{
	t_page		*page;
	t_block		*block;

	page = find_free_page(head, size);
	if (page)
	{
		if((block = new_block(page, size))){
			if (!IS_MAGIC(block->magic))
				return (get_head(head, size));
			page->space += SIZE(size);
			return (block++);
		}
		return (NULL);
	}
	if (!get_new_page(head, size))
		return (NULL);
	return (get_head(head, size));
}

t_block		*get_large(t_page **head, size_t size)
{
	t_page		*page;
	t_block		*new;

	if (!(page = get_new_large_page(head, size)))
		return (NULL);
	new = init_block((uint64_t)page + PAGE_H, size, NULL, NULL);
	return (new++);
	
}

void		*ft_malloc(size_t size)
{
	if (!size)
		return (NULL);
	if (size > SMALL)
		return(get_large(&g_store_mem.large, size));
	return (get_head(size > TINY ? &g_store_mem.small : &g_store_mem.tiny, size));
}
