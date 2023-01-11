/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jquivogn <jquivogn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 02:15:18 by jquivogn          #+#    #+#             */
/*   Updated: 2023/01/11 19:18:49 by jquivogn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

t_page			*g_first_page;
pthread_mutex_t	mutex;
int i = 0;

void		*get_alloc(size_t size)
{
	t_page		*page;
	t_block		*block;

	if ((page = find_free_page(size))){
		if ((block = new_block(page, size))){
			// print_block(block, i);
			i++;
			return (GOTO_M(block));
		}
	}
	ft_putstr("[MALLOC FAIL]\n");
	return (NULL);
}

void		*malloc(size_t size)
{
	void	*mem;

	pthread_mutex_lock(&mutex);
	// ft_putstr("[START MALLOC]\n");
	if (size == 0){
		ft_putstr("[MALLOC SIZE == 0]\n");
		pthread_mutex_unlock(&mutex);
		return (NULL);
	}
	mem = get_alloc(size);
	// ft_putstr("[E--------------------M]\n");
	pthread_mutex_unlock(&mutex);
	return (mem);
}
