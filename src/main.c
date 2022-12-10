/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jquivogn <jquivogn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 02:17:51 by jquivogn          #+#    #+#             */
/*   Updated: 2022/12/10 10:21:07 by jquivogn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

int	main()
{
	void *ptr;

	ptr = malloc(12);
	printf("%p\n", ptr);
	ptr = malloc(12);
	printf("%p\n", ptr);
	ptr = malloc(12);
	printf("%p\n", ptr);
	ptr = malloc(12);
	printf("%p\n", ptr);
	return 0;
}