# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jojo <jojo@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/10 02:23:08 by jquivogn          #+#    #+#              #
#    Updated: 2022/12/15 00:17:51 by jojo             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

CC = gcc

# CFLAGS = -Wall -Wextra -Werror -g

FLAGS = -lft -fPIC

PROJECT_NAME = malloc

NAME = libft_malloc_$(HOSTTYPE).so
LINK = libft_malloc.so

INCLUDE = -I ./includes/

SRC_PATH = ./src
INC_PATH = ./includes
OBJ_PATH = ./obj

SRC_NAME =	malloc.c\
			page.c\
			block.c\
			utils.c\
			free.c\
			show_alloc_mem.c\
			main.c
			# realloc.c\

INC_NAME =	malloc.h

OBJ_NAME = $(SRC_NAME:.c=.o)

SRC = $(addprefix $(SRC_PATH)/, $(SRC_NAME))
INC = $(addprefix $(INC_PATH)/, $(INC_NAME))
OBJ = $(addprefix $(OBJ_PATH)/, $(OBJ_NAME))

all: logo $(NAME)

$(NAME): $(OBJ) $(INC)
	@$(CC) $(CFLAGS) $(INCLUDE) $(OBJ) -o $(NAME)
	@echo "\033[38;2;0;255;255mfiller\t\033[1;33mCompilation\t\t\033[0;32m[OK]\033[0m"
	@echo "\033[38;2;0;255;255mfiller\t\033[38;2;255;0;0m$(NAME)\t\t\033[0;32m[OK]\033[0m"

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	@mkdir $(dir $(OBJ_PATH)/$*) 2> /dev/null || true
	@echo "\033[38;2;0;255;0m[cc]\033[0m: $< -> $@"
	@printf "\e[1A"
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@
	@printf "\e[0K"
# $(NAME): $(OBJ) $(INC)
# 	@$(CC) $(CFLAGS) -shared -o $@ $(OBJ) -L $(FLAGS)
# 	@ln -sf $(NAME) $(LINK)
# 	@echo "\033[38;2;0;255;255m$(PROJECT_NAME)\t\033[1;33mCompilation\t\t\t\033[0;32m[OK]\033[0m"
# 	@echo "\033[38;2;0;255;255m$(PROJECT_NAME)\t\033[38;2;255;0;0m$(NAME)\t\033[0;32m[OK]\033[0m"

# $(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
# 	@mkdir $(dir $(OBJ_PATH)/$*) 2> /dev/null || true
# 	@echo "\033[38;2;0;255;0m[cc]\033[0m: $< -> $@"
# 	@printf "\e[1A"
# 	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@
# 	@printf "\e[0K"

clean:
	@rm -rf $(OBJ) $(OBJ_PATH)
	@echo "\033[38;2;0;255;255m$(PROJECT_NAME)\t\033[1;33mCleaning obj\t\t\033[0;32m[OK]\033[0m"

fclean: clean
	@rm -rf $(NAME)
	@echo "\033[38;2;0;255;255m$(PROJECT_NAME)\t\033[1;33mCleaning exe\t\t\033[0;32m[OK]\033[0m"

logo:
	@echo ""
	@echo  "\033[38;2;255;128;0m::::    ::::      :::     :::        :::        ::::::::   ::::::::  "
	@echo "\033[38;2;255;105;21m+:+:+: :+:+:+   :+: :+:   :+:        :+:       :+:    :+: :+:    :+:"
	@echo  "\033[38;2;255;84;42m+:+ +:+:+ +:+  +:+   +:+  +:+        +:+       +:+    +:+ +:+        "
	@echo  "\033[38;2;255;63;63m+#+  +:+  +#+ +#++:++#++: +#+        +#+       +#+    +:+ +#+        "
	@echo  "\033[38;2;255;42;84m+#+       +#+ +#+     +#+ +#+        +#+       +#+    +#+ +#+        "
	@echo "\033[38;2;255;21;105m#+#       #+# #+#     #+# #+#        #+#       #+#    #+# #+#    #+#"
	@echo  "\033[38;2;255;0;128m###       ### ###     ### ########## ########## ########   ########  "
	@echo "\033[0m    \033[38;2;0;255;191m"

re: fclean all

.PHONY: all clean fclean re logo