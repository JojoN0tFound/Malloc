/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jquivogn <jquivogn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 02:15:18 by jquivogn          #+#    #+#             */
/*   Updated: 2022/12/17 12:11:48 by jquivogn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

t_heap		g_store_mem;

t_block		*get_alloc(t_page **head, size_t size)
{
	t_page		*page;
	t_block		*block;

	page = find_free_page(head, size);
	if (page){
		if((block = new_block(page, size))){
			page->space += SIZE(MOD_BASE(size));
			return (GOTO_M(block));
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
	new = init_block(ADDR(page->first), size, NULL, NULL);
	page->space += SIZE(MOD_BASE(size));
	return (GOTO_M(new));
	
}

void		*malloc(size_t size)
{
	if (!size)
		return (NULL);
	if (size > SMALL)
		return(get_large_alloc(&g_store_mem.large, size));
	return (get_alloc(get_head(size), size));
}
