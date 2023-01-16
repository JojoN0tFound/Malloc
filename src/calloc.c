/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jojo <jojo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 16:11:26 by jquivogn          #+#    #+#             */
/*   Updated: 2023/01/16 00:51:13 by jojo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

void		*calloc(size_t elementCount, size_t elementSize)
{
	void	*mem;

	if (elementCount < 0 || elementSize < 0)//check elementCount * elementSize > max int
		return (NULL);
	pthread_mutex_lock(&mutex);
	C_S
	mem = get_alloc(elementCount * elementSize);
	mem = ft_memset(mem, 0, mod_base(elementCount * elementSize));
	C_E
	pthread_mutex_unlock(&mutex);
	return (mem);
}