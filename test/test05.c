/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test05.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jquivogn <jquivogn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 00:16:11 by jojo              #+#    #+#             */
/*   Updated: 2022/12/21 03:27:49 by jquivogn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ********************************** */
/*                                    */
/*               TEST 5               */
/*                                    */
/* ********************************** */

#include "../includes/malloc.h"

int	main(void)
{
	char *ptr;
	char *ptr1;
	char *ptr2;
	int i = 0;

	ptr = malloc(124);
	while (i < 100){
		ptr[i] = 42;
		i++;
	}
	ptr1 = malloc(31);
	ptr2 = malloc(76);
	// free(ptr);
	free(ptr1);
	// free(ptr2);
	// ptr = malloc(1024 * 1024 * 16);
	// ptr = malloc(1024 * 1024 * 128);
	show_alloc_mem();
	print_alloc_mem(M_MEM);
	print_alloc_mem(F_MEM);
	print_alloc_mem(P_HEADER);
	print_alloc_mem(B_HEADER);
	print_alloc_mem(M_MEM | F_MEM);
	print_alloc_mem(M_MEM | P_HEADER);
	print_alloc_mem(M_MEM | B_HEADER);
	print_alloc_mem(M_MEM | F_MEM | P_HEADER);
	print_alloc_mem(M_MEM | F_MEM | B_HEADER);
	print_alloc_mem(M_MEM | P_HEADER);
	print_alloc_mem(F_MEM | P_HEADER);
	print_alloc_mem(F_MEM | B_HEADER);
	print_alloc_mem(F_MEM | P_HEADER | B_HEADER);
	print_alloc_mem(P_HEADER | B_HEADER);
	print_alloc_mem(M_MEM | F_MEM | P_HEADER | B_HEADER);
	return (0);
}