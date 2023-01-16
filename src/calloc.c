/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jojo <jojo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 16:11:26 by jquivogn          #+#    #+#             */
/*   Updated: 2023/01/16 17:28:15 by jojo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

void		*calloc(size_t elementCount, size_t elementSize)
{
	void	*mem;

	pthread_mutex_lock(&mutex);
	if (elementCount < 0 || elementSize < 0 || elementCount * elementSize > ULONG_MAX)
		return (NULL);
	// C_S
	pthread_mutex_unlock(&mutex);
	mem = malloc(elementCount * elementSize);
	pthread_mutex_lock(&mutex);
	mem = ft_memset(mem, 0, mod_base(elementCount * elementSize));
	// C_E
	pthread_mutex_unlock(&mutex);
	return (mem);
}