# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ytouihar <ytouihar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/01 17:07:57 by bsuc              #+#    #+#              #
#    Updated: 2024/03/21 17:57:10 by ytouihar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_DIR = src
PARS_DIR = $(SRC_DIR)/parsing

PARS_SRC = \
	$(PARS_DIR)/parsing_chars.c \
	$(PARS_DIR)/parsing_map.c \
	$(PARS_DIR)/parsing_map2.c \
	$(PARS_DIR)/parsing_sanitize.c \
	$(PARS_DIR)/parsing_struct.c \
	$(PARS_DIR)/parsing_utils.c \
	$(PARS_DIR)/parsing.c \
	$(PARS_DIR)/right_side.c \
	$(PARS_DIR)/parsing_utils2.c
	

SRC = \
	$(PARS_SRC) \
	$(SRC_DIR)/game_init.c \
	$(SRC_DIR)/sanitize.c \
	$(SRC_DIR)/raycasting.c \
	$(SRC_DIR)/get_distance.c \
	$(SRC_DIR)/render.c \
	$(SRC_DIR)/mlx_pixel.c \
	$(SRC_DIR)/key_event.c \
	$(SRC_DIR)/trigo_utils.c \
	$(SRC_DIR)/main.c \
	$(SRC_DIR)/game_init_utils_bonus.c \
	$(SRC_DIR)/pistol_bonus.c \
	$(SRC_DIR)/pistol_utils_bonus.c \
	$(SRC_DIR)/minimap.c \
	$(SRC_DIR)/door_animations.c \
	$(SRC_DIR)/fog_bonus.c \
	$(SRC_DIR)/game_init_doors_bonus.c \
	$(SRC_DIR)/render_doors_utils.c \
	$(SRC_DIR)/render_doors.c
	

OBJ_DIR = src/obj
OBJ = $(addprefix $(OBJ_DIR)/, $(notdir $(SRC:.c=.o)))
#OBJ_BONUS = $(addprefix $(OBJ_DIR)/, $(notdir $(SRC_BONUS:.c=.o))
NAME = cub3d
LIBFT = libft/libft.a

CC = cc
CFLAGS = -Wall -Wextra -O3 #-Werror #-g
LIB = -Lminilibx-linux -lmlx -lXext -lX11 -lm
INC = -Iminilibx-linux -I./headers

RM = rm -rf

all : $(NAME)

$(NAME): $(OBJ_DIR) $(OBJ) $(LIBFT)
# make -C minilibx-linux
	$(CC) $(CFLAGS) $(OBJ) $(LIB) $(INC) $(LIBFT) -o $(NAME)

$(OBJ_DIR):
	mkdir -p $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(OBJ_DIR)/%.o: $(PARS_DIR)/%.c
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(LIBFT) :
	make -C libft all

clean :
	make -C libft clean
	$(RM) $(OBJ_DIR)

fclean : clean
	make -C libft fclean
	$(RM) $(NAME)

re : fclean all
