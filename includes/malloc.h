/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jojo <jojo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 02:19:22 by jquivogn          #+#    #+#             */
/*   Updated: 2023/01/20 09:03:56 by jojo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

/*
** include
*/
# include <unistd.h>
# include <sys/mman.h>
# include <pthread.h>
# include <inttypes.h>

/*
** define
*/
# define TRUE 1
# define FALSE 0

# define FREE 0x2
# define USED 0x1
# define MAGIC 0xDEADCAFEBEEF0000
# define IS_MAGIC(x) (MAGIC == (x & 0xFFFFFFFFFFFF0000))
# define IS_FREE(x) (FREE == (x & FREE))
# define IS_USED(x) (USED == (x & USED))

# define TINY 64
# define SMALL 1024

# define TINY_PAGE (4 * getpagesize())
# define SMALL_PAGE (26 * getpagesize())

# define BLOCK_H sizeof(t_block)
# define PAGE_H sizeof(t_page)

# define ADDR(x) (uint64_t)x
# define FIRST(x) (t_block *)(ADDR(x) + PAGE_H)

# define GOTO_M(x) (void *)(ADDR(x) + BLOCK_H)
# define GOTO_H(x) (t_block *)(ADDR(x) - BLOCK_H)

# define INFO 0
# define HEX 1

/*
** color define
*/
# define P(x) write(1, x, ft_strlen(x));
# define WHI "\e[0m"
# define DRK "\e[30m"
# define RED "\e[31m"
# define GRN "\e[32m"
# define ORA "\e[33m"
# define BLU "\e[34m"
# define PUR "\e[35m"
# define CYA "\e[36m"

/*
** enum
*/
typedef enum	e_type
{
					T, // TINY
					S, // SMALL
					L  // LARGE
}				t_type;

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
	t_type			type;
	uint64_t		fill;
	uint64_t		max;
	struct s_page	*next;
}				t_page;

/*
** extern declaration
*/
extern t_page			*g_first_page;
extern pthread_mutex_t	mutex;

/*
** lib malloc
*/
void		*malloc(size_t size);
void		free(void *ptr);
void		*realloc(void *ptr, size_t size);
void 		show_alloc_mem();

/*
** lib malloc bonus
*/
void		*calloc(size_t count, size_t size);
size_t		malloc_usable_size(void *ptr);
void		print_hex_block(void *ptr);


/*
** malloc.c
*/
void		*get_alloc(size_t size);

/*
** realloc.c
*/
void		*get_new_alloc(void *ptr, size_t size);

/*
** free.c
*/
int			free_block(void *ptr);

/*
** page.c
*/
t_page		*find_free_page(t_block **block,size_t size);
t_page		*find_block_page(uint64_t a_block);

/*
** block.c
*/
t_block		*init_block(uint64_t addr, size_t free, size_t size, t_block *prev, t_block *next);
t_block		*split_block(t_block *block, size_t size);

/*
** utils.c
*/
t_type		get_type(size_t size);
size_t		get_page_size(size_t size);
size_t		page_base(size_t size);
size_t		mod_base(size_t size);

/*
** print.c
*/
void		ft_print_memory(const void *addr, size_t size);
void		print_block(t_block *block, int nb);
void		print_all_block(t_block *block, int flag);

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