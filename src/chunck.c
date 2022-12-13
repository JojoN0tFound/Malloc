/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chunck.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jquivogn <jquivogn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 18:56:07 by jquivogn          #+#    #+#             */
/*   Updated: 2022/12/13 20:27:08 by jquivogn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

void		add_new_to_memory(t_chunck **head, t_chunck *new)
{
	t_chunck	*tmp;

	tmp = *head;
	if (!tmp)
	{
		*head = new;
		return ;
	}
	while(tmp && tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

t_chunck		*find_free_chunck(t_chunck **head, size_t size)
{
	t_chunck	*tmp;

	tmp = *head;
	while (tmp)
	{
		if (size + BLOCK_H <= tmp->max - tmp->space)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

int			get_new_chunck(t_chunck **head, size_t size)
{
	t_chunck	*new;
	size_t		block_size;
	size_t		chunck_size;

	block_size = get_block_size(size) + BLOCK_H;
	chunck_size = block_size * 100 + CHUNCK_H;
	new = (t_chunck *)mmap(NULL, PAGE_BASE(chunck_size),
		PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	if (!new)
		return (FALSE);
	new->max = PAGE_BASE(chunck_size);
	new->space = 0;
	new->next = NULL;
	add_new_to_memory(head, new);
	return (TRUE);
}

int			get_new_large_chunck(t_chunck **head, size_t size)
{
	t_chunck	*new;
	size_t		block_size;
	size_t		chunck_size;

	block_size = get_block_size(size) + BLOCK_H;
	chunck_size = block_size + CHUNCK_H;
	new = (t_chunck *)mmap(NULL, PAGE_BASE(chunck_size),
		PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	if (!new)
		return (FALSE);
	new->max = PAGE_BASE(chunck_size);
	new->space = 0;
	new->next = NULL;
	add_new_to_memory(head, new);
	return (TRUE);
}