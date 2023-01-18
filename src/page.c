/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   page.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jquivogn <jquivogn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 18:56:07 by jquivogn          #+#    #+#             */
/*   Updated: 2022/12/13 20:27:08 by jquivogn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

int			is_continuous_space(t_page *page, size_t size)
{
	t_block	*block = FIRST(page);

	while (block){
		if (IS_FREE(block->magic) && block->size >= mod_base(size))
			return (TRUE);
		block = block->next;
	}

	return (FALSE);
}

void		add_new_to_memory(t_page *new)
{
	t_page	*page = g_first_page;

	if (!page){
		g_first_page = new;
		return ;
	}

	while(page && page->next)
		page = page->next;
	page->next = new;
}

t_page		*get_new_page(size_t size)
{
	t_page	*new_page;
	size_t	page_size;

	page_size = get_page_size(size);
	new_page = (t_page *)mmap(NULL, page_size,
		PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);

	if (new_page == MAP_FAILED)
		return (NULL);

	new_page->type = get_type(size);
	new_page->fill = 0;
	new_page->max = page_size - PAGE_H;
	new_page->next = NULL;

	if (new_page->type != L){
		ft_putstr("+++");
		ft_putulnbr(new_page->max - BLOCK_H);
		N
	}
	if (new_page->type == L)
		init_block(ADDR(FIRST(new_page)), (MAGIC | USED), size, NULL, NULL);
	else
		init_block(ADDR(FIRST(new_page)), (MAGIC | FREE), new_page->max - BLOCK_H, NULL, NULL);

	add_new_to_memory(new_page);

	return (new_page);
}

t_page	*find_free_page(size_t size)
{
	t_page	*page = g_first_page;

	if (get_type(size) == L)
		return (get_new_page(size));

	while (page){
		if (get_type(size) == page->type && is_continuous_space(page, size))
			return (page);
		page = page->next;
	}

	return (get_new_page(size));
}