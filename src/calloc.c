/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jquivogn <jquivogn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 16:11:26 by jquivogn          #+#    #+#             */
/*   Updated: 2023/01/18 17:58:00 by jquivogn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

void		*calloc(size_t count, size_t size)
{
	void	*mem;

	if (count < 0 || size < 0 || count * size / count != size)
		return (NULL);

	pthread_mutex_lock(&mutex);

	mem = get_alloc(count * size);
	mem = ft_memset(mem, 0, mod_base(count * size));

	pthread_mutex_unlock(&mutex);

	return (mem);
}