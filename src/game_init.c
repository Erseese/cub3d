/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytouihar <ytouihar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 18:00:02 by bsuc              #+#    #+#             */
/*   Updated: 2024/03/21 16:33:24 by ytouihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	dir_ang(t_game *game, int i, int j)
{
	if (game->parsing->map[i][j] == 'N')
		game->play_ang = M_PI_2;
	else if (game->parsing->map[i][j] == 'S')
		game->play_ang = (3 * M_PI) / 2;
	else if (game->parsing->map[i][j] == 'E')
		game->play_ang = 0;
	else if (game->parsing->map[i][j] == 'W')
		game->play_ang = M_PI;
}

static void	play_pos(t_game *game)
{
	int	i;
	int	j;

	i = -1;
	while (game->parsing->map[++i])
	{
		j = -1;
		while (game->parsing->map[i][++j] != '\n')
		{
			if (ft_strchr("NSEW", game->parsing->map[i][j]))
			{
				game->pos_x = j;
				game->pos_y = i;
				game->play_x = j * IMG_SIZE + IMG_SIZE / 2;
				game->play_y = i * IMG_SIZE + IMG_SIZE / 2;
				dir_ang(game, i, j);
				return ;
			}
		}
	}
}

static void	put_text(t_game *game, t_mlx t, int val)
{
	if (val == 0)
		game->text[0] = t;
	if (val == 1)
		game->text[1] = t;
	if (val == 2)
		game->text[2] = t;
	if (val == 3)
		game->text[3] = t;
}

static void	init_text(t_game *game, int val)
{
	t_mlx	t;
	int		x;
	int		y;

	x = IMG_SIZE;
	y = IMG_SIZE;
	if (val == 0)
		t.img = mlx_xpm_file_to_image(game->mlx, game->parsing->north, &x, &y);
	if (val == 1)
		t.img = mlx_xpm_file_to_image(game->mlx, game->parsing->south, &x, &y);
	if (val == 2)
		t.img = mlx_xpm_file_to_image(game->mlx, game->parsing->east, &x, &y);
	if (val == 3)
		t.img = mlx_xpm_file_to_image(game->mlx, game->parsing->west, &x, &y);
	if (!t.img)
	{
		free_ptr(game);
		mlx_destroy_window(game->mlx, game->win);
		mlx_destroy_display(game->mlx);
		free(game->mlx);
		handle_error("Malloc problem ptr img\n", game->parsing, 1);
	}
	t.addr = mlx_get_data_addr(t.img, &t.bpp, &t.l_len, &t.endian);
	put_text(game, t, val);
}

void	game_init(t_game *game, t_parse *p)
{
	ft_memset(game, 0, sizeof(t_game));
	game->parsing = p;
	game->mlx = mlx_init();
	if (!game->mlx)
		handle_error("MLX INIT ERROR\n", p, 1);
	game->win = mlx_new_window(game->mlx, WIN_WIDTH, WIN_HEIGHT, "Game");
	if (!game->win)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
		handle_error("Mlx new window error\n", p, 1);
	}
	init_text(game, 0);
	init_text(game, 1);
	init_text(game, 2);
	init_text(game, 3);
	game->floor = ((p->f_red << 16) | (p->f_green << 8) | p->f_blue);
	game->ceiling = ((p->c_red << 16) | (p->c_green << 8) | p->c_blue);
	play_pos(game);
	game->fov_ang = M_PI / 3;
	game->ray_ang = game->play_ang + (game->fov_ang / 2);
	game_init_bonus(game);
}
