/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jquivogn <jquivogn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 02:19:22 by jquivogn          #+#    #+#             */
/*   Updated: 2022/12/10 08:44:20 by jquivogn         ###   ########.fr       */
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

/*
** define
*/
# define TRUE 1
# define FALSE 0

# define FREE 1
# define USED 0

# define BLOCK_SIZE 16

# define TINY 256
# define SMALL 1024

/*
** struct
*/
typedef struct	s_block
{
	size_t			size;
	int				free;
	struct s_block	*next;
	struct s_block	*prev;
}				t_block;

typedef struct	s_memory
{
	t_block			*tiny;
	t_block			*small;
	t_block			*large;
}				t_memory;

extern t_memory		g_store_mem;

/*
** malloc.c
*/
void	*malloc(size_t size);

/*
** realloc.c
*/
void	*realloc(void *ptr, size_t size);

/*
** free.c
*/
void	free(void *ptr);

/*
** utils.c
*/

#endif