# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marvin <marvin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/31 18:09:50 by bsuc              #+#    #+#              #
#    Updated: 2024/03/17 18:50:59 by marvin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

GNL_DIR = gnl
OBJ_DIR = obj

GNL_SRC = $(GNL_DIR)/get_next_line_utils.c \
	$(GNL_DIR)/get_next_line.c \

LIBFT_SRC = \
	ft_strchr.c \
	ft_strlen.c \
	ft_strncmp.c \
	ft_strrchr.c \
	ft_memset.c \
	ft_strdup.c \
	ft_atoi.c \
	ft_isdigit.c \
	ft_memset.c \
	ft_substr.c \
	ft_putstr_fd.c

SRC = $(GNL_SRC) $(LIBFT_SRC)

OBJS = $(addprefix $(OBJ_DIR)/, $(notdir $(SRC:.c=.o)))
INC = -I./headers
NAME = libft.a
CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -rf

all : $(NAME)

$(NAME) : $(OBJ_DIR) $(OBJS)
	ar rc $(NAME) $(OBJS)

$(OBJ_DIR):
	mkdir -p $@

$(OBJ_DIR)/%.o : $(GNL_DIR)/%.c
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(OBJ_DIR)/%.o : %.c
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

clean :
	$(RM) $(OBJ_DIR)
	
fclean : clean
	$(RM) $(NAME)
	
re : fclean all
