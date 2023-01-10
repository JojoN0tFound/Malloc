/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jquivogn <jquivogn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 20:55:01 by jquivogn          #+#    #+#             */
/*   Updated: 2023/01/10 17:02:32 by jquivogn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

// void	print_octet(size_t *printed, const unsigned char* pc, int i)
// {
// 	int g;

// 	g = (*(pc+i) >> 4) & 0xf;
// 	g += g >= 10 ? 'a'-10 : '0';
// 	ft_putchar(g);
// 	(*printed)++;
// 	g = *(pc+i) & 0xf;
// 	g += g >= 10 ? 'a'-10 : '0';
// 	ft_putchar(g);
// 	(*printed)++;
// 	if (*printed % 32 == 0)
// 		N
// 	else if (*printed % 4 == 0)
// 		ft_putchar(' ');
// }

// void	print_memory(const void *addr, size_t size, char *color)
// {
// 	size_t printed;
// 	size_t i;
// 	const unsigned char* pc;

// 	printed = 0;
// 	i = 0;
// 	pc = addr;
// 	while (i < size){
// 		if (printed % 32 == 0){
// 			ft_putstr(WHI);
// 			ft_putaddr(ADDR(addr) + i);
// 			ft_putchar(' ');
// 		}
// 		ft_putstr(color);
// 		print_octet(&printed, pc, i);
// 		i++;
// 	}
// 	ft_putstr(RED);
// 	while (printed % 32 != 0)
// 		print_octet(&printed, pc, i);
// 	ft_putstr(WHI);
// }

// void	block_dump(t_block *block, int flag)
// {
// 	if (flag & B_HEADER)
// 		print_memory((void *)block, BLOCK_H, BLU);
// 	else {
// 		ft_putaddr(ADDR(block));
// 		ft_putstr(" ...\n");
// 	}
// 	if (flag & M_MEM)
// 		print_memory((void *)block + BLOCK_H, block->size, GRN);
// 	else if (!(flag & M_MEM) && (flag & B_HEADER)){
// 		ft_putaddr(ADDR(block) + BLOCK_H);
// 		ft_putstr(" ...\n");
// 	}
// }

// void	page_dump(t_page **head_page, int flag)
// {
// 	t_page	*tmp;
// 	t_block	*block;
// 	size_t	ret;

// 	if (flag & NONE)
// 		return ;
// 	tmp = *head_page;
// 	while (tmp){
// 		ft_putstr("==============\n");
// 		if (flag & P_HEADER)
// 			print_memory((void *)tmp, PAGE_H, YEL);
// 		else {
// 			ft_putaddr(ADDR(tmp));
// 			ft_putstr(" ...\n");
// 		}
// 		block = tmp->first;
// 		while (block){
// 			if (tmp->first == block && (ADDR(tmp) + PAGE_H) != ADDR(block)){
// 				if (flag & F_MEM)
// 					print_memory((void *)(ADDR(tmp) + PAGE_H), ADDR(block) - (ADDR(tmp) + PAGE_H), LGR);
// 				else {
// 					ft_putaddr(ADDR(tmp) + PAGE_H);
// 					ft_putstr(" ...\n");
// 				}
// 			}
// 			if (block->prev){
// 				ret = SIZE(ADDR(block->prev)) + MOD_BASE(block->prev->size);
// 				if (ret < ADDR(block)){
// 					if (flag & F_MEM)
// 						print_memory((void *)ret, ADDR(block) - ret, LGR);
// 					else {
// 						ft_putaddr(ret);
// 						ft_putstr(" ...\n");
// 					}
// 				}
// 			}
// 			block_dump(block, flag);
// 			if (!block->next){
// 				ret = SIZE(ADDR(block)) + MOD_BASE(block->size);
// 				if (ret < ADDR(tmp) + PAGE_H + page_base(tmp->max)){
// 					if (flag & F_MEM)
// 						print_memory((void *)ret, ADDR(tmp) + PAGE_H + page_base(tmp->max) - ret, LGR);
// 					else {
// 						ft_putaddr(ret);
// 						ft_putstr(" ...\n");
// 					}
// 				}
// 			}
// 			block = block->next;
// 		}
// 		tmp = tmp->next;
// 	}
// }

// void	print_alloc_mem(int flag)
// {
// 	t_page	*tiny;
// 	t_page	*small;
// 	t_page	*large;

// 	if (flag == NONE)
// 		return ;
// 	// pthread_mutex_lock(&mutex);
// 	tiny = g_store_mem.tiny;
// 	small = g_store_mem.small;
// 	large = g_store_mem.large;
// 	if (tiny)
// 		page_dump(&tiny, flag);
// 	// if (small)
// 	// 	page_dump(&small, flag);
// 	// if (large)
// 	// 	page_dump(&large, flag);
// 	// pthread_mutex_unlock(&mutex);
// }

void print_memory(const void *addr, size_t size)
{
	size_t printed;
	size_t i;
	const unsigned char* pc;
	int g;

	printed = 0;
	i = 0;
	pc = addr;
	while (i < size){
		g = (*(pc+i) >> 4) & 0xf;
		g += g >= 10 ? 'a'-10 : '0';
		ft_putchar(g);
		printed++;
		g = *(pc+i) & 0xf;
		g += g >= 10 ? 'a'-10 : '0';
		ft_putchar(g);
		printed++;
		if (printed % 32 == 0)
			ft_putchar('\n');
		else if (printed % 4 == 0)
			ft_putchar(' ');
		i++;
	}
}

void	print_block(t_block *block, int nb)
{
	ft_putstr("=========BLOCK========\n");
	if (nb != -1){
		ft_putstr("block nb: ");
		ft_putnbr(nb);
		ft_putchar('\n');
	}
	ft_putstr("block  addr: ");
	ft_putaddr((uint64_t)block);
	ft_putstr("\naddr  magic: ");
	ft_putaddr(block->magic);
	ft_putstr("\nblock size: ");
	ft_putnbr(block->size);
	ft_putstr("\nblock prev: ");
	ft_putaddr((uint64_t)block->prev);
	ft_putstr("\nblock next: ");
	ft_putaddr((uint64_t)block->next);
	ft_putstr("\n======================\n");
}

void	print_all_block(t_block *block)
{
	int i = 0;
	while (block){
		print_block(block, i);
		block = block->next;
		i++;
	}
}