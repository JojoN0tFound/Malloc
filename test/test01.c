/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test01.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jquivogn <jquivogn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 00:16:11 by jojo              #+#    #+#             */
/*   Updated: 2023/01/18 18:17:15 by jquivogn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ********************************** */
/*                                    */
/*               TEST 1               */
/*                                    */
/* ********************************** */

// # echo "=====================TEST 1====================="
// # echo "================================================"
// # echo "Nous testons le nombre de page reclaim en allouant"
// # echo "1024 * 1024 bytes pour le comparer au test 0"
// # echo "PR test 1 - PR test 0 = PR par le malloc "
// # echo "================================================\n"

#include "../includes/malloc.h"
#include <stdlib.h>

int	main()
{
	int		i;
	char	*addr;

	i = 0;
	while (i < 1024)
	{
		addr = (char*)malloc(1024);
		addr[0] = 42;
		i++;
	}
	return (0);
}