/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_usable_size.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jojo <jojo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 22:02:55 by jojo              #+#    #+#             */
/*   Updated: 2023/01/19 22:06:46 by jojo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

size_t		malloc_usable_size(void *ptr)
{
	t_block	*block = GOTO_H(ptr);

	if (!ptr || !find_block_page(ADDR(block)) || !IS_MAGIC(block->magic))
		return (0);

	return (mod_base(block->size));
}