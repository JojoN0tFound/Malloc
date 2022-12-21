/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test04.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jquivogn <jquivogn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 00:16:11 by jojo              #+#    #+#             */
/*   Updated: 2022/12/21 06:22:20 by jquivogn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ********************************** */
/*                                    */
/*               TEST 4               */
/*                                    */
/* ********************************** */

#include <string.h>
#include <unistd.h>
#include "../includes/malloc.h"

void	print(char *s)
{
	write(1, s, strlen(s));
}

int		main(void)
{
	// char *addr;

	// addr = malloc(16);
	// free(NULL);
	// free((void *)addr + 5);
	// if (realloc((void *)addr + 5, 10) == NULL)
	// 	print("Bonjours\n");
	void *ptr;
	void *ptr1;
	void *ptr2;

	ptr = malloc(4096);
	ptr1 = malloc(1556);
	ptr2 = malloc(3792);
	free(ptr);
	return (0);
}