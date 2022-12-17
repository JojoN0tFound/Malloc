/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jquivogn <jquivogn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 02:19:22 by jquivogn          #+#    #+#             */
/*   Updated: 2022/12/17 12:22:16 by jquivogn         ###   ########.fr       */
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

# define FREE 0x2
# define USED 0x1

# define TINY 128
# define SMALL 1024

# define BLOCK_H sizeof(t_block)
# define PAGE_H sizeof(t_page)
# define SIZE(x) x + BLOCK_H

# define ADDR(x) (uint64_t)x

# define GOTO_M(x) (void *)(ADDR(x) + BLOCK_H)
# define GOTO_H(x) (t_block *)(ADDR(x) - BLOCK_H)

# define MOD_BASE(x) x + (16 - (x % 16))
# define PAGE_BASE(x) x + getpagesize() - (x % getpagesize())

# define MAGIC 0xDEADCAFEBEEF0000
# define IS_MAGIC(x) (MAGIC == (x & 0xFFFFFFFFFFFF0000))

# define TEST write(1, "TEST\n", 5);
# define DEBUG write(1, "DEBUG\n", 6);
# define ERROR write(1, "ERROR\n", 6);
# define SEGV write(1, "SEGV\n", 5);
# define COUCOU write(1, "coucou\n", 7);
# define TOTO write(1, "toto\n", 5);
# define YO write(1, "yo\n", 3);
# define N write(1, "\n", 1);

/*
** struct
*/
typedef struct	s_block
{
	uint64_t		magic;
	size_t			size;
	struct s_block	*prev;
	struct s_block	*next;
}				t_block;

typedef struct	s_page
{
	int				space;
	size_t			max;
	t_block			*first;
	struct s_page	*next;
}				t_page;

typedef struct	s_heap
{
	t_page			*tiny;
	t_page			*small;
	t_page			*large;
}				t_heap;

extern t_heap	g_store_mem;

/*
** malloc.c
*/
t_block		*get_alloc(t_page **head, size_t size);
t_block		*get_large_alloc(t_page **head, size_t size);
void		*malloc(size_t size);

/*
** page.c
*/
void		add_new_to_memory(t_page **head, t_page *new);
t_page		*find_free_page(t_page **head, size_t size);
int			get_new_page(t_page **head, size_t size);
t_page		*get_new_large_page(t_page **head, size_t size);

/*
** block.c
*/
t_block		*init_block(uint64_t addr, size_t size, void *prev, void *next);
size_t		get_block_size(size_t size);
t_block		*new_block(t_page *page, size_t size);

/*
** realloc.c
*/
void		*realloc(void *ptr, size_t size);

/*
** free.c
*/
void		free_block(t_page **page, t_block *block);
void		free_page(void *ptr);
void		free(void *ptr);

/*
** show_alloc_mem.c
*/
void		show_block(t_block *block);
size_t		show_page(t_page **head_page, char *type);
void 		show_alloc_mem();

/*
** utils.c
*/
t_page		**get_head(size_t size);

/*
** print.c
*/
void		print_memory(const void *addr, size_t size);
void		print_block(t_block *block, int nb);
void		print_all_block(t_block *block);

/*
** libft.c
*/
void		*ft_memcpy(void *s1, const void *s2, size_t n);
void		ft_putnbr(int nb);
int			ft_strlen(char* str);
void		ft_putstr(char const *s);
void		ft_putchar(char c);
void		ft_putaddr(uint64_t number);

#endif