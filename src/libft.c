/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jquivogn <jquivogn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 20:56:08 by jquivogn          #+#    #+#             */
/*   Updated: 2022/12/19 16:15:11 by jquivogn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

void	*ft_memcpy(void *s1, const void *s2, size_t n)
{
	size_t	i;
	char	*dest;
	char	*src;

	i = 0;
	dest = (char *)s1;
	src = (char *)s2;
	while (i < n)
	{
		dest[i] = src[i];
		i++;
	}
	return ((void *)dest);
}

void	*ft_memset(void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((unsigned char *)s)[i] = c;
		i++;
	}
	return (s);
}

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putstr(char const *s)
{
	while (*s)
		ft_putchar(*s++);
}

int		ft_strlen(char* str)
{
	int	i;

	i = 0;
	while(str[i])
		i++;
	return (i);
}

void	ft_putnbr(int nb)
{
	if (nb < 0)
	{
		ft_putchar('-');
		if (nb == -2147483648) {
			nb = -147483648;
			ft_putchar('2');
		}
		nb *= -1;
	}
	if (nb > 9)
		ft_putnbr(nb / 10);
	ft_putchar((nb % 10) + 48);
}

void	ft_putaddr(uint64_t number)
{
	char ans[16];
	char comp[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C',
			'D', 'E', 'F'};
	int i = 0;

	ft_putstr("0x");
	while (number / 16) {
		ans[i++] = comp[number % 16];
		number /= 16;
	}
	ans[i] = comp[number % 16];
	while (i >= 0) {
		while (ans[i] == 0)
			i--;
		ft_putchar(ans[i--]);
	}
}