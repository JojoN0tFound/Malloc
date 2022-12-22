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

t_page	*find_free_page(t_page **head, size_t size)
{
	t_page	*page;

	page = *head;
	while (page){
		if (page->space >= size && is_continuous_space(page, size))
			return (page);
		page = page->next;
	}
	return (NULL);
}

void		add_new_to_memory(t_page **head, t_page *new)
{
	t_page	*tmp;

	tmp = *head;
	if (!tmp){
		*head = new;
		return ;
	}
	while(tmp && tmp->next){
		tmp = tmp->next;
	}
	tmp->next = new;
}

t_page		*get_new_page(t_page **head, size_t size)
{
	t_page	*page;

	page = (t_page *)mmap(NULL, MAX(mod_base(size)) + PAGE_H,
		PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	if (!page)
		return (NULL);
	page->next = NULL;
	page->space = MAX(mod_base(size));
	init_block(ADDR(FIRST(page)), (MAGIC | FREE), page->space, NULL, NULL);
	add_new_to_memory(head, page);
	return (page);
}