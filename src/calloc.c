/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jojo <jojo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 16:11:26 by jquivogn          #+#    #+#             */
/*   Updated: 2023/01/19 01:29:51 by jojo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

void		*calloc(size_t count, size_t size)
{
	void	*mem;

	if (count < 0 || size <= 0 || count * size / count != size){
		BRUH
		sleep(500);
		return (NULL);
	}

	pthread_mutex_lock(&mutex);

	// C_S
	mem = get_alloc(count * size);
	mem = ft_memset(mem, 0, mod_base(count * size));

	// C_E
	pthread_mutex_unlock(&mutex);

	return (mem);
}