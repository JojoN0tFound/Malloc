/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jquivogn <jquivogn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 02:19:22 by jquivogn          #+#    #+#             */
/*   Updated: 2022/12/21 09:48:56 by jquivogn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

/*
** include
*/
# include <unistd.h>
# include <string.h>
# include <sys/mman.h>
# include <sys/time.h>
# include <sys/resource.h>
# include <stdio.h>
# include <limits.h>
# include <inttypes.h>
# include <pthread.h>

/*
** define
*/
# define TRUE 1
# define FALSE 0

# define FREE 0x2
# define USED 0x1

# define TINY 128
# define SMALL 1024

# define NONE 0x0
# define M_MEM 0x1
# define F_MEM 0x10
# define B_HEADER 0x100
# define P_HEADER 0x1000

# define BLOCK_H sizeof(t_block)
# define PAGE_H sizeof(t_page)
# define SIZE(x) x + BLOCK_H

# define ADDR(x) (uint64_t)x

# define GOTO_M(x) (void *)(ADDR(x) + BLOCK_H)
# define GOTO_H(x) (t_block *)(ADDR(x) - BLOCK_H)

# define MOD_BASE(x) x + (x % 16 == 0 ? 0 : 16 - (x % 16))

# define MAGIC 0xDEADCAFEBEEF0000
# define IS_MAGIC(x) (MAGIC == (x & 0xFFFFFFFFFFFF0000))

# define WHI "\033[0m"
# define LGR "\033[0;37m"
# define DGR "\033[1;30m"
# define YEL "\033[1;33m"
# define GRN "\033[0;32m"
# define CYA "\033[0;36m"
# define BLU "\033[1;34m"
# define RED "\033[0;31m"

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
	size_t			max;
	int				space;
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

extern pthread_mutex_t mutex;

/*
** malloc.c
*/
t_block		*get_alloc(t_page **head, size_t size);
t_block		*get_large_alloc(t_page **head, size_t size);
void		*malloc(size_t size);

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
** calloc.c
*/
void		*calloc(size_t elementCount, size_t elementSize);

/*
** page.c
*/
t_page		*find_free_page(t_page **head, size_t size);
void		add_new_to_memory(t_page **head, t_page *new);
int			get_new_page(t_page **head, size_t size);
t_page		*get_new_large_page(t_page **head, size_t size);

/*
** block.c
*/
t_block		*init_block(uint64_t addr, size_t size, void *prev, void *next);
t_block		*new_block(t_page *page, size_t size);

/*
** utils.c
*/
t_page		**get_head(size_t size);
size_t		get_block_size(size_t size);
size_t		page_base(size_t size);
int			is_continuous_space(t_page *page, size_t size);

/*
** print.c
*/
void		print_memory(const void *addr, size_t size, char *color);
void		print_alloc_mem(int flag);
void		print_block(t_block *block, int nb);
void		print_all_block(t_block *block);

/*
** libft.c
*/
void		*ft_memcpy(void *s1, const void *s2, size_t n);
void		*ft_memset(void *s, int c, size_t n);
void		ft_putnbr(int nb);
void		ft_putulnbr(size_t nb);
int			ft_strlen(char* str);
void		ft_putstr(char const *s);
void		ft_putchar(char c);
void		ft_putaddr(uint64_t number);

#endif