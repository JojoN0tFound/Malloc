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
	t_page	*tmp;

	tmp = *head;
	while (tmp){
		if ((SIZE(size) <= (size_t)(tmp->max - tmp->space)) && is_continuous_space(tmp, size)){
			return (tmp);
		}
		tmp = tmp->next;
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

int			get_new_page(t_page **head, size_t size)
{
	t_page	*new;
	size_t	block_size;
	size_t	page_size;

	block_size = SIZE(get_block_size(size));
	page_size = page_base(block_size * 100 + PAGE_H);
	new = (t_page *)mmap(NULL, page_size,
		PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	if (!new)
		return (FALSE);
	new->max = page_size - PAGE_H;
	new->first = NULL;
	new->space = 0;
	new->next = NULL;
	add_new_to_memory(head, new);
	return (TRUE);
}

t_page		*get_new_large_page(t_page **head, size_t size)
{
	t_page	*new;
	size_t	block_size;
	size_t	page_size;

	block_size = SIZE(size);
	page_size = page_base(block_size + PAGE_H);
	new = (t_page *)mmap(NULL, page_size,
		PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	if (!new)
		return (NULL);
	new->max = page_size - PAGE_H;
	new->first = NULL;
	new->space = 0;
	new->next = NULL;
	SEGV
	add_new_to_memory(head, new);
	return (new);
}