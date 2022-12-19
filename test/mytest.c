/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mytest.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jojo <jojo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 02:17:51 by jquivogn          #+#    #+#             */
/*   Updated: 2022/12/19 01:44:33 by jojo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

int	main()
{
	char	*ptr;
	char	*ptr1;
	char	*ptr2;
	void	*ptr3;

/*
** TINY
*/
	ft_putstr("===============================TINY=========\n");
	ft_putstr("============================================\n\n");
	ptr = malloc(11);
	ptr1 = malloc(112);
	ptr2 = malloc(15);
	ptr3 = malloc(64);
	show_alloc_mem();
	print_all_block(g_store_mem.tiny->first);
	ft_putstr("======================================== FREE 112\n\n");
	free(ptr1);
	show_alloc_mem();
	ft_putstr("====================================== MALLOC 12\n\n");
	ptr1 = malloc(12);
	show_alloc_mem();
	ft_putstr("==================================== REALLOC 15 -> 98\n\n");
	ptr2 = realloc(ptr2, 98);
	show_alloc_mem();
	ft_putstr("======================================= FREE 11\n\n");
	free(ptr);
	show_alloc_mem();
	ft_putstr("======================================= FREE 64\n\n");
	free(ptr3);
	show_alloc_mem();
	ft_putstr("======================================= FREE 15\n\n");
	free(ptr2);
	show_alloc_mem();
	ft_putstr("======================================= FREE 12\n\n");
	free(ptr1);
	show_alloc_mem();
	ft_putstr("============================================\n\n");

/*
** SMALL
*/
	ft_putstr("=========SMALL========\n");
	ft_putstr("======================\n\n");
	ptr = malloc(1000);
	ptr1 = realloc(ptr1, 850);
	ptr2 = malloc(560);
	ptr3 = malloc(1024);
	show_alloc_mem();
	ft_putstr("======================\n\n");
	free(ptr);
	free(ptr1);
	free(ptr2);
	free(ptr3);
	show_alloc_mem();
	ft_putstr("======================\n\n");

/*
** LARGE
*/
	ft_putstr("=========LARGE========\n");
	ft_putstr("======================\n\n");
	ptr = realloc(ptr, 5678);
	show_alloc_mem();
	ptr1 = realloc(ptr1, 1234);
	show_alloc_mem();
	ptr2 = realloc(ptr2, 9854);
	show_alloc_mem();
	ptr3 = realloc(ptr3, 1025);
	show_alloc_mem();
	ft_putstr("======================\n\n");
	free(ptr3);
	free(ptr2);
	free(ptr);
	free(ptr1);
	show_alloc_mem();
	ft_putstr("======================\n\n");

	return 0;
}