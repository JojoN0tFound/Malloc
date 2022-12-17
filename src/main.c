/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jquivogn <jquivogn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 02:17:51 by jquivogn          #+#    #+#             */
/*   Updated: 2022/12/17 19:49:51 by jquivogn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

	/* ********************************************************************* */
	/*                                                                       */
	/*                                TEST 1                                 */
	/*                                                                       */
	/* ********************************************************************* */

// int	main()
// {
// 	int		i;
// 	char	*addr;

// 	i = 0;
// 	while (i < 1024)
// 	{
// 		i++;
// 	}
// 	return (0);
// }

	/* ********************************************************************* */
	/*                                                                       */
	/*                                TEST 2                                 */
	/*                                                                       */
	/* ********************************************************************* */

// int	main()
// {
// 	int		i;
// 	char	*addr;

// 	i = 0;
// 	while (i < 1024)
// 	{
// 		addr = (char*)malloc(1024);
// 		addr[0] = 42;
// 		i++;
// 	}
// 	return (0);
// }

	/* ********************************************************************* */
	/*                                                                       */
	/*                                TEST 3                                 */
	/*                                                                       */
	/* ********************************************************************* */

#include <string.h>

#define M 1024 * 1024

void	print(char *s)
{
	write(1, s, strlen(s));
}

int		main(void)
{
	char *addr1;
	char *addr2;
	char *addr3;

	addr1 = malloc(16 * M);
	strcpy(addr1, "Bonjours\n");
	print(addr1);
	addr2 = malloc(16 * M);
	addr3 = realloc(addr1, 128 * M);
	addr3[127 * M] = 42;
	print(addr3);
	return (0);
}

	/* ********************************************************************* */
	/*                                                                       */
	/*                                TEST 4                                 */
	/*                                                                       */
	/* ********************************************************************* */

// #include <string.h>

// void	print(char *s)
// {
// 	write(1, s, strlen(s));
// }

// int		main(void)
// {
// 	char *addr;

// 	addr = malloc(16);
// 	free(NULL);
// 	free((void *)addr + 5);
// 	if (realloc((void *)addr + 5, 10) == NULL)
// 		print("Bonjours\n");
// 	return (0);
// }

	/* ********************************************************************* */
	/*                                                                       */
	/*                                TEST 5                                 */
	/*                                                                       */
	/* ********************************************************************* */

// int	main(void)
// {
// 	malloc(1024);
// 	malloc(1024 * 32);
// 	malloc(1024 * 1024);
// 	malloc(1024 * 1024 * 16);
// 	malloc(1024 * 1024 * 128);
// 	show_alloc_mem();
// 	return (0);
// }

	/* ********************************************************************* */
	/*                                                                       */
	/*                                MY TEST                                */
	/*                                                                       */
	/* ********************************************************************* */

// int	main()
// {
	// char	*ptr;
	// char	*ptr1;
	// char	*ptr2;
	// void	*ptr3;

// /*
// ** TINY
// */
	// ft_putstr("===============================TINY=========\n");
	// ft_putstr("============================================\n\n");
	// ptr = malloc(11);
	// ptr1 = malloc(112);
	// ptr2 = malloc(15);
	// ptr3 = malloc(64);
	// show_alloc_mem();
	// print_all_block(g_store_mem.tiny->first);
	// ft_putstr("======================================== FREE 112\n\n");
	// free(ptr1);
	// show_alloc_mem();
	// ft_putstr("====================================== MALLOC 12\n\n");
	// ptr1 = malloc(12);
	// show_alloc_mem();
	// ft_putstr("==================================== REALLOC 15 -> 98\n\n");
	// ptr2 = realloc(ptr2, 98);
	// show_alloc_mem();
	// ft_putstr("======================================= FREE 11\n\n");
	// free(ptr);
	// show_alloc_mem();
	// ft_putstr("======================================= FREE 64\n\n");
	// free(ptr3);
	// show_alloc_mem();
	// ft_putstr("======================================= FREE 15\n\n");
	// free(ptr2);
	// show_alloc_mem();
	// ft_putstr("======================================= FREE 12\n\n");
	// free(ptr1);
	// show_alloc_mem();
	// ft_putstr("============================================\n\n");
	
// /*
// ** SMALL
// */
	// ft_putstr("=========SMALL========\n");
	// ft_putstr("======================\n\n");
	// ptr = malloc(1000);
	// ptr1 = realloc(ptr1, 850);
	// ptr2 = malloc(560);
	// ptr3 = malloc(1024);
	// show_alloc_mem();
	// ft_putstr("======================\n\n");
	// free(ptr);
	// free(ptr1);
	// free(ptr2);
	// free(ptr3);
	// show_alloc_mem();
	// ft_putstr("======================\n\n");



// /*
// ** LARGE
// */
	// ft_putstr("=========LARGE========\n");
	// ft_putstr("======================\n\n");
	// ptr = realloc(ptr, 5678);
	// show_alloc_mem();
	// ptr1 = realloc(ptr1, 1234);
	// show_alloc_mem();
	// ptr2 = realloc(ptr2, 9854);
	// show_alloc_mem();
	// ptr3 = realloc(ptr3, 1025);
	// show_alloc_mem();
	// ft_putstr("======================\n\n");
	// free(ptr3);
	// free(ptr2);
	// free(ptr);
	// free(ptr1);
	// show_alloc_mem();
	// ft_putstr("======================\n\n");

// 	return 0;
// }