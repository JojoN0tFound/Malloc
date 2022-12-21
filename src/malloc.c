/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jquivogn <jquivogn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 02:15:18 by jquivogn          #+#    #+#             */
/*   Updated: 2022/12/21 13:58:29 by jquivogn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

t_heap			g_store_mem;
pthread_mutex_t	mutex;

t_block		*get_alloc(t_page **head, size_t size)
{
	t_page		*page;
	t_block		*block;

	page = find_free_page(head, size);
	if (page){
		if((block = new_block(page, size))){
			page->space += SIZE(mod_base(size));
			return (GOTO_M(block));
		}
	}
	if (!(page = get_new_page(head, SIZE(get_block_size(size)) * 100)))
		return (NULL);
	if((block = new_block(page, size))){
		page->space += SIZE(mod_base(size));
		return (GOTO_M(block));
	}
	return (NULL);
}

t_block		*get_large_alloc(t_page **head, size_t size)
{
	t_page		*page;
	t_block		*new;

	if (!(page = get_new_page(head, SIZE(size))))
		return (NULL);
	new = init_block(ADDR(page) + PAGE_H, size, NULL, NULL);
	page->space += SIZE(mod_base(size));
	page->first = new;
	return (GOTO_M(new));
}

void		*malloc(size_t size)
{
	void	*mem;

	pthread_mutex_lock(&mutex);
	// ft_putstr("================================= MALLOC ===============================\n");
	// ft_putulnbr(size);
	// N
	// show_alloc_mem();
	if (size == 0)
		return (NULL);
	if (size > SMALL)
		mem = get_large_alloc(&g_store_mem.large, size);
	else
		mem = get_alloc(get_head(size), size);
	// ft_putstr("&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&\n");
	pthread_mutex_unlock(&mutex);
	if (mem == NULL)
		BRUH
	return (mem);
}
