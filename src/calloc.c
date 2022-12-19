/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jquivogn <jquivogn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 16:11:26 by jquivogn          #+#    #+#             */
/*   Updated: 2022/12/19 17:01:45 by jquivogn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

void		*calloc(size_t elementCount, size_t elementSize)
{
	void	*mem;

	pthread_mutex_lock(&mutex);
	if (elementCount == 0 || elementSize == 0){
		pthread_mutex_unlock(&mutex);
		return (NULL);
	}
	mem = malloc(elementCount * elementSize);
	if (mem){
		mem = ft_memset(mem, 0, elementCount * elementSize);
	}
	pthread_mutex_unlock(&mutex);
	return (mem);
}