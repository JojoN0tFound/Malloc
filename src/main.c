/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jojo <jojo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 02:17:51 by jquivogn          #+#    #+#             */
/*   Updated: 2022/12/14 17:39:03 by jojo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

int	main()
{
	void	*ptr;
	void	*ptr1;
	void	*ptr2;
	void	*ptr3;

/*
** TINY
*/
	ft_putstr("=========TINY=========\n");
	ft_putstr("======================\n\n");
	ptr = ft_malloc(11);
	ptr1 = ft_malloc(112);
	ptr2 = ft_malloc(15);
	ptr3 = ft_malloc(64);
	ft_putstr("======================\n\n");
/*
** SMALL
*/
	ft_putstr("=========SMALL========\n");
	ft_putstr("======================\n\n");
	ptr = ft_malloc(1000);
	ptr1 = ft_malloc(850);
	ptr2 = ft_malloc(560);
	ptr3 = ft_malloc(1024);
	ft_putstr("======================\n\n");
/*
** LARGE
*/
	ft_putstr("=========LARGE========\n");
	ft_putstr("======================\n\n");
	ptr = ft_malloc(5678);
	ptr1 = ft_malloc(1234);
	ptr2 = ft_malloc(9854);
	ptr3 = ft_malloc(1025);
	ft_putstr("======================\n\n");



	show_alloc_mem();

	return 0;
}