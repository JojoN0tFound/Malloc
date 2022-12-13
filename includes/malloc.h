/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jquivogn <jquivogn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 02:19:22 by jquivogn          #+#    #+#             */
/*   Updated: 2022/12/13 20:54:08 by jquivogn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

/*
** include
*/
# include <unistd.h>
# include <sys/mman.h>
# include <sys/time.h>
# include <sys/resource.h>
# include <stdio.h>
# include <limits.h>
# include <inttypes.h>

/*
** define
*/
# define TRUE 1
# define FALSE 0

# define FREE 0x1
# define USED 0x2

# define BLOCK_H 16
# define CHUNCK_H 32

# define TINY 256
# define SMALL 1024

# define PAGE_BASE(x) x + getpagesize() - (x % getpagesize())

# define MAGIC 0xDEADCAFEBEEF0000
# define IS_MAGIC(x) (MAGIC == (x & 0xFFFFFFFFFFFF0000))

# define MOD_BASE(x) x + (16 - (x % 16))

# define TEST write(1, "TEST\n", 5);
# define DEBUG write(1, "DEBUG\n", 6);
# define SEGV write(1, "SEGV\n", 5);
# define COUCOU write(1, "coucou\n", 7);
# define TOTO write(1, "toto\n", 5);
# define YO write(1, "yo\n", 3);

/*
** struct
*/
typedef struct	s_block
{
	uint64_t		free;
	size_t			size;
}				t_block;

typedef struct	s_chunck
{
	uint64_t		space;
	uint64_t		max;
	struct s_chunck	*next;
}				t_chunck;

typedef struct	s_heap
{
	t_chunck		*tiny;
	t_chunck		*small;
	t_chunck		*large;
}				t_heap;

extern t_heap		g_store_mem;

/*
** malloc.c
*/
void		*ft_malloc(size_t size);
t_block		*new_block(t_chunck *chunck, size_t size);
size_t		get_block_size(size_t size);
t_block		*get_head(t_chunck **head, size_t size);

/*
** chunck.c
*/
void		add_new_to_memory(t_chunck **head, t_chunck *new);
t_chunck	*find_free_chunck(t_chunck **head, size_t size);
int			get_new_chunck(t_chunck **head, size_t size);
int			get_new_large_chunck(t_chunck **head, size_t size);

/*
** realloc.c
*/
void	*realloc(void *ptr, size_t size);

/*
** free.c
*/
void	free(void *ptr);

/*
** show_alloc_mem.c
*/
void 	show_alloc_mem();

/*
** free.c
*/
void	ft_putnbr(int nb);
int		ft_strlen(char* str);
void	ft_putstr(char const *s);
void	ft_putchar(char c);
void	print_memory(const void *addr, size_t size);

#endif