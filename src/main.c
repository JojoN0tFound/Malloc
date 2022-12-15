/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jojo <jojo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 02:17:51 by jquivogn          #+#    #+#             */
/*   Updated: 2022/12/15 01:51:07 by jojo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

int	main()
{
	void	*ptr;
	void	*ptr1;
	char	*ptr2;
	void	*ptr3;

/*
** TINY
*/
	ft_putstr("=========TINY=========\n");
	ft_putstr("======================\n\n");
	ptr = malloc(11);
	ptr1 = malloc(112);
	ptr2 = malloc(15);
	ptr3 = malloc(64);
	show_alloc_mem();
	ft_putstr("======================\n\n");
	free(ptr1);
	show_alloc_mem();
	ft_putstr("======================\n\n");
	ptr1 = malloc(12);
	show_alloc_mem();
	ft_putstr("======================\n\n");
	free(ptr);
	free(ptr3);
	free(ptr2);
	free(ptr1);
	ft_putstr("======================\n\n");
	
/*
** SMALL
*/
	// ft_putstr("=========SMALL========\n");
	// ft_putstr("======================\n\n");
	// ptr = malloc(1000);
	// ptr1 = malloc(850);
	// ptr2 = malloc(560);
	// ptr3 = malloc(1024);
	// ft_putstr("======================\n\n");
/*
** LARGE
*/
	// ft_putstr("=========LARGE========\n");
	// ft_putstr("======================\n\n");
	// ptr = malloc(5678);
	// ptr1 = malloc(1234);
	// ptr2 = malloc(9854);
	// ptr3 = malloc(1025);
	// show_alloc_mem();
	// ft_putstr("======================\n\n");
	// free(ptr3);
	// free(ptr2);
	// free(ptr);
	// free(ptr1);
	// ft_putstr("======================\n\n");



	// show_alloc_mem();

	return 0;
}