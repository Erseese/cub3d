/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytouihar <ytouihar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 15:45:31 by marvin            #+#    #+#             */
/*   Updated: 2024/03/21 18:31:48 by ytouihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	get_color(t_game *game, int flag, int i, int slice)
{
	int	offset;
	int	color;

	if (flag == 0 || flag == 1)
		offset = (int)game->hit_wall.x % (int)IMG_SIZE;
	else
		offset = (int)game->hit_wall.y % (int)IMG_SIZE;
	color = pixel_get(&game->text[flag], offset, i * (IMG_SIZE / slice));
	return (color);
}

static void	render_wall(t_game *game, int slice, int pos, int flag)
{
	int				y;
	int				i;
	unsigned int	color;

	i = -1;
	while (++i < slice)
	{
		y = (WIN_HEIGHT / 2) - (slice / 2) + i;
		color = get_color(game, flag, i, slice);
		game->intensity = (game->distance - 64) / game->distance;
		if (game->distance > 64)
			color = colorize(color, game->intensity);
		if (y <= WIN_HEIGHT && y >= 0)
			my_mlx_pixel_put(&game->img, pos, y, color);
	}
}

static void	render_floor(t_game *game, int slice, int pos)
{
	int				y;
	unsigned int	color;

	y = 0;
	while (y < (WIN_HEIGHT / 2) - (slice / 2))
	{
		color = 0;
		game->intensity = (game->distance - 64) / game->distance;
		if (game->distance > 64)
			color = colorize(color, game->intensity);
		my_mlx_pixel_put(&game->img, pos, y, color);
		y++;
	}
	y = (WIN_HEIGHT / 2) + (slice / 2);
	while (y < WIN_HEIGHT)
	{
		color = 0;
		game->intensity = (game->distance - 64) / game->distance;
		if (game->distance > 64)
			color = colorize(color, game->intensity);
		my_mlx_pixel_put(&game->img, pos, y, color);
		y++;
	}
}

int	render(t_game *game)
{
	int		ray;
	int		slice;
	int		flag;
	double	dist_view;

	dist_view = (WIN_WIDTH / 2.) / tan(game->fov_ang / 2.);
	game->ray_ang = game->play_ang + (game->fov_ang / 2);
	ray = -1;
	while (++ray < WIN_WIDTH)
	{
		flag = eval_distance(game);
		slice = round(IMG_SIZE / game->distance * dist_view);
		render_wall(game, slice, ray, flag);
		render_floor(game, slice, ray);
		//print_door(game, game->curr_ang, ray);
		game->ray_ang -= (((double)FOV / (double)WIN_WIDTH) * M_PI / 180.);
		check_max_trigo(game->ray_ang);
	}
	doors_state(game);
	minimap(game->parsing->map_copy, game);
	pistol(game);
	cursor(game);
	check_pas_mes_ennemis(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
	return (0);
}
