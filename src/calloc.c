/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jojo <jojo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 16:11:26 by jquivogn          #+#    #+#             */
/*   Updated: 2023/01/08 20:21:59 by jojo             ###   ########.fr       */
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
	pthread_mutex_unlock(&mutex);
	mem = malloc(elementCount * elementSize);
	pthread_mutex_lock(&mutex);
	if (mem){
		mem = ft_memset(mem, 0, elementCount * elementSize);
	}
	pthread_mutex_unlock(&mutex);
	return (mem);
}