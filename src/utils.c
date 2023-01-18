/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jquivogn <jquivogn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 02:40:31 by jquivogn          #+#    #+#             */
/*   Updated: 2023/01/18 23:44:51 by jquivogn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

t_type		get_type(size_t size)
{
	if (size <= TINY)
		return (T);
	else if (size <= SMALL)
		return (S);
	return (L);
}

size_t		get_page_size(size_t size)
{
	if (get_type(size) == T)
		return (TINY_PAGE);
	else if (get_type(size) == S)
		return (SMALL_PAGE);
	else
		return (page_base(mod_base(size) + BLOCK_H + PAGE_H));
}

size_t		page_base(size_t size)
{
	size_t	size_page = getpagesize();
	size_t	ret = size % size_page;

	ret = ret == 0 ? 0 : size_page - ret;
	return (size + ret);
}

size_t		mod_base(size_t size)
{
	int	ret = size % 16;
	
	ret = ret == 0 ? 0 : (16 - ret);
	return (size + ret);
}