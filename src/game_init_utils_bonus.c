/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init_utils_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytouihar <ytouihar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 16:32:09 by ytouihar          #+#    #+#             */
/*   Updated: 2024/03/21 18:39:21 by ytouihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

long	get_current_time(long times)
{
	struct timespec	time;

	if (clock_gettime(CLOCK_MONOTONIC, &time) == -1)
		write(2, "clock_gettime() error\n", 23);
	return (time.tv_sec * 1000 + time.tv_nsec / 1000000 - times);
}

static void	put_textures_bonus(t_game *game, t_mlx t, int val)
{
	if (val == 0)
		game->door = t;
	if (val == 1)
		game->pistol = t;
}

static void	init_textures_bonus(t_game *game, int val)
{
	t_mlx	t;
	int		x;
	int		y;

	x = IMG_SIZE;
	y = IMG_SIZE;
	if (val == 0)
		t.img = mlx_xpm_file_to_image(game->mlx, "textures/door.xpm", &x, &y);
	if (val == 1)
		t.img = mlx_xpm_file_to_image(game->mlx, "textures/piou.xpm", &x, &y);
	if (!t.img)
	{
		free_ptr(game);
		mlx_destroy_window(game->mlx, game->win);
		mlx_destroy_display(game->mlx);
		free(game->mlx);
		handle_error("Malloc problem ptr img\n", game->parsing, 1);
	}
	t.addr = mlx_get_data_addr(t.img, &t.bpp, &t.l_len, &t.endian);
	put_textures_bonus(game, t, val);
}

void	game_init_bonus(t_game *game)
{
	t_mlx	test;
	int		i;

	i = 0;
	game->minimap_size = MINIMAP_SIZE;
	if (game->minimap_size % 2 == 0)
		game->minimap_size++;
	game->start_timer = get_current_time(get_current_time(0));
	game->longline = find_longest_line(game->parsing->map, &i);
	test.img = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
	test.addr = mlx_get_data_addr(test.img, &test.bpp, &test.l_len, \
	&test.endian);
	init_textures_bonus(game, 0);
	init_textures_bonus(game, 1);
	game->img = test;
}
