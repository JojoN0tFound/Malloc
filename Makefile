# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jquivogn <jquivogn@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/10 02:23:08 by jquivogn          #+#    #+#              #
#    Updated: 2022/12/21 11:07:11 by jquivogn         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

CC = gcc

# CFLAGS = -Wall -Wextra -Werror -g

FLAGS = -fPIC

LIB_MALLOC = -L. -lft_malloc

PROJECT_NAME = malloc

NAME = libft_malloc_$(HOSTTYPE).so
LINK = libft_malloc.so

INCLUDE = -I ./includes/

SRC_PATH = ./src
INC_PATH = ./includes
OBJ_PATH = ./obj

SRC_NAME =	malloc.c\
			realloc.c\
			free.c\
			page.c\
			block.c\
			show_alloc_mem.c\
			utils.c\
			print.c\
			libft.c\

INC_NAME =	malloc.h

OBJ_NAME = $(SRC_NAME:.c=.o)

SRC = $(addprefix $(SRC_PATH)/, $(SRC_NAME))
INC = $(addprefix $(INC_PATH)/, $(INC_NAME))
OBJ = $(addprefix $(OBJ_PATH)/, $(OBJ_NAME))

all: logo $(NAME)
	@ln -sf $(NAME) $(LINK)

$(NAME): $(OBJ) $(INC)
	@$(CC) $(CFLAGS) -shared -o $@ $(OBJ)
	@echo "\033[38;2;0;255;255m$(PROJECT_NAME)\t\033[1;33mCompilation\t\t\t\033[0;32m[OK]\033[0m"
	@echo "\033[38;2;0;255;255m$(PROJECT_NAME)\t\033[38;2;255;0;0m$(NAME)\t\033[0;32m[OK]\033[0m"

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c Makefile
	@mkdir $(dir $(OBJ_PATH)/$*) 2> /dev/null || true
	@echo "\033[38;2;0;255;0m[cc]\033[0m: $< -> $@"
	@printf "\e[1A"
	@$(CC) $(CFLAGS) $(FLAGS) -c $< -o $@
	@printf "\e[0K"

clean:
	@rm -rf $(OBJ) $(OBJ_PATH)
	@echo "\033[38;2;0;255;255m$(PROJECT_NAME)\t\033[1;33mCleaning obj\t\t\033[0;32m[OK]\033[0m"

fclean: clean tclean
	@rm -rf $(NAME) $(LINK)
	@echo "\033[38;2;0;255;255m$(PROJECT_NAME)\t\033[1;33mCleaning exe\t\t\033[0;32m[OK]\033[0m"

test: re
	@clang -fPIC $(LIB_MALLOC) test/test00.c -o test00
	@clang -fPIC $(LIB_MALLOC) test/test01.c -o test01
	@clang -fPIC $(LIB_MALLOC) test/test02.c -o test02
	@clang -fPIC $(LIB_MALLOC) test/test03.c -o test03
	@clang -fPIC $(LIB_MALLOC) test/test04.c -o test04
	@clang -fPIC $(LIB_MALLOC) test/test05.c -o test05
	@clang -fPIC $(LIB_MALLOC) test/mytest.c -o mytest
	@echo "\033[38;2;0;255;255m$(PROJECT_NAME)\t\033[38;2;255;0;0mCreating tests\t\033[0;32m[OK]\033[0m"

tclean:
	@rm -rf test00 test01 test02 test03 test04 test05 mytest
	@echo "\033[38;2;0;255;255m$(PROJECT_NAME)\t\033[1;33mCleaning tests\t\t\033[0;32m[OK]\033[0m"

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

.PHONY: all test clean fclean re logo
