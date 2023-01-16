/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jojo <jojo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 02:40:31 by jquivogn          #+#    #+#             */
/*   Updated: 2023/01/16 00:46:16 by jojo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

size_t		get_block_size(size_t size)
{
	if (size <= TINY)
		return (TINY);
	else if (size <= SMALL)
		return (SMALL);
	return (size);
}

size_t		get_page_size(size_t size)
{
	if (get_block_size(size) == TINY)
		return (TINY_PAGE);
	else if (get_block_size(size) == SMALL)
		return (SMALL_PAGE);
	else
		return (page_base(SIZE(size) + PAGE_H));
}

t_type		get_type(size_t size)
{
	if (size <= TINY)
		return (T);
	else if (size <= SMALL)
		return (S);
	return (L);
}

size_t		page_base(size_t size)
{
	size_t	size_page;
	size_t	ret;

	size_page = getpagesize();
	ret = size % size_page;
	ret = ret == 0 ? 0 : size_page - ret;
	return (size + ret);
}

size_t		mod_base(size_t size)
{
	int	ret;

	ret = size % 16;
	ret = ret == 0 ? 0 : (16 - ret);
	return (size + ret);
}
