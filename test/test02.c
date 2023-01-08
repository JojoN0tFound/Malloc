/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test02.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jojo <jojo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 00:16:11 by jojo              #+#    #+#             */
/*   Updated: 2023/01/08 16:43:30 by jojo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ********************************** */
/*                                    */
/*               TEST 2               */
/*                                    */
/* Test du free des pages reclaims    */
/* l'objectif est d'arriver a +3 par  */
/* rapport au test 0                  */
/*                                    */
/* ********************************** */

#include "../includes/malloc.h"
#include <stdlib.h>

int		main(void)
{
	int		i;
	char	*addr;

	i = 0;
	while (i < 1024)
	{
		addr = (char*)malloc(1024);
		addr[0] = 42;
		free(addr);
		i++;
	}
	return (0);
}