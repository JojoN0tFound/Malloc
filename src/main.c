/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jquivogn <jquivogn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 02:17:51 by jquivogn          #+#    #+#             */
/*   Updated: 2022/12/13 20:55:44 by jquivogn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

int	main()
{
	void *ptr;
	void *ptr1;
	void *ptr2;
	void *ptr3;

/*
** TINY
*/
	ft_putstr("=========TINY=========\n");
	ft_putstr("======================\n\n");
	ptr = ft_malloc(175);
	print_memory(ptr-16, 16);
	ft_putchar('\n');
	// printf("%p\n", ptr);
	ft_putstr("\n\n======================\n\n");
	ptr1 = ft_malloc(15);
	print_memory(ptr1-16, 16);
	ft_putchar('\n');
	// printf("%p\n", ptr1);
	ft_putstr("\n\n======================\n\n");
	ptr2 = ft_malloc(50);
	print_memory(ptr2-16, 16);
	ft_putchar('\n');
	// printf("%p\n", ptr2);
	ft_putstr("\n\n======================\n\n");
	ptr3 = ft_malloc(64);
	print_memory(ptr3-16, 16);
	ft_putchar('\n');
	// printf("%p\n", ptr3);
	ft_putstr("\n\n======================\n\n");
/*
** SMALL
*/
	// printf("========SMALL=========\n");
	// printf("======================\n");
	// ptr = ft_malloc(2000);
	// printf("%p\n", ptr);
	// printf("======================\n");
	// ptr1 = ft_malloc(2000);
	// printf("%p\n", ptr1);
	// printf("======================\n");
	// ptr2 = ft_malloc(2000);
	// printf("%p\n", ptr2);
	// printf("======================\n");
	// ptr3 = ft_malloc(2000);
	// printf("%p\n", ptr3);
/*
** LARGE
*/
	// printf("========LARGE=========\n");
	// printf("======================\n\n");
	// ptr = ft_malloc(100000);
	// printf("%p\n", ptr);
	// printf("\n======================\n\n");
	// ptr1 = ft_malloc(2000);
	// printf("%p\n", ptr1);
	// printf("\n======================\n\n");
	// ptr2 = ft_malloc(2000);
	// printf("%p\n", ptr2);
	// printf("\n======================\n\n");
	// ptr3 = ft_malloc(2000);
	// printf("%p\n", ptr3);
	// printf("\n======================\n\n");

	return 0;
}