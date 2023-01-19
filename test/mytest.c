/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mytest.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jojo <jojo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 02:17:51 by jquivogn          #+#    #+#             */
/*   Updated: 2023/01/19 22:14:09 by jojo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"
#include <stdlib.h>

int	main()
{
	char	*ptr;
	char	*ptr1;
	char	*ptr2;
	void	*ptr3;


	ft_putstr("=================== TINY ===================\n");
	ft_putstr("============================================\n\n");
	ft_putstr("====================================== MALLOC 11\n\n");
	ptr = malloc(11);
	show_alloc_mem();
	ft_putstr("====================================== MALLOC 112\n\n");
	ptr1 = malloc(112);
	show_alloc_mem();
	ft_putstr("====================================== MALLOC 15\n\n");
	ptr2 = malloc(15);
	show_alloc_mem();
	ft_putstr("====================================== MALLOC 64\n\n");
	ptr3 = malloc(64);
	show_alloc_mem();
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
	ft_putstr("======================================= FREE 98\n\n");
	free(ptr2);
	show_alloc_mem();
	ft_putstr("======================================= FREE 12\n\n");
	free(ptr1);
	show_alloc_mem();
	ft_putstr("============================================\n\n");


	ft_putstr("=================== SMALL ===================\n");
	ft_putstr("=============================================\n\n");
	ft_putstr("======================================== MALLOC 1000\n\n");
	ptr = malloc(1000);
	show_alloc_mem();
	ft_putstr("======================================== REALLOC 12 -> 850\n\n");
	ptr1 = realloc(ptr1, 850);
	show_alloc_mem();
	ft_putstr("======================================== MALLOC 560\n\n");
	ptr2 = malloc(560);
	show_alloc_mem();
	ft_putstr("======================================== MALLOC 1024\n\n");
	ptr3 = malloc(1024);
	show_alloc_mem();
	ft_putstr("======================================== FREE 850\n\n");
	free(ptr1);
	show_alloc_mem();
	ft_putstr("======================================== FREE 560\n\n");
	free(ptr2);
	show_alloc_mem();
	ft_putstr("=============================================\n\n");


	ft_putstr("=================== LARGE ===================\n");
	ft_putstr("=============================================\n\n");
	ft_putstr("======================================== REALLOC 1000 -> 5678\n\n");
	ptr = realloc(ptr, 5678);
	show_alloc_mem();
	ft_putstr("======================================== REALLOC 850 -> 1234\n\n");
	ptr1 = realloc(ptr1, 1234);
	show_alloc_mem();
	ft_putstr("======================================== REALLOC 560 -> 9854\n\n");
	ptr2 = realloc(ptr2, 9854);
	show_alloc_mem();
	ft_putstr("======================================== REALLOC 1024 -> 1025\n\n");
	ptr3 = realloc(ptr3, 1025);
	show_alloc_mem();
	ft_putstr("======================================== FREE 1025\n\n");
	free(ptr3);
	show_alloc_mem();
	ft_putstr("======================================== FREE 9854\n\n");
	free(ptr2);
	show_alloc_mem();
	ft_putstr("======================================== FREE 5678\n\n");
	free(ptr);
	show_alloc_mem();
	ft_putstr("======================================== FREE 1234\n\n");
	free(ptr1);
	show_alloc_mem();
	ft_putstr("=============================================\n\n");


	return 0;
}