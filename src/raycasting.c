/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytouihar <ytouihar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 16:04:32 by marvin            #+#    #+#             */
/*   Updated: 2024/03/21 18:04:15 by ytouihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_wall(t_game *game, t_coor *inter, int horiz)
{
	int		len;
	long	map_y;
	double	cpy_x;
	double	cpy_y;

	cpy_x = inter->x;
	cpy_y = inter->y;
	if (horiz && sin(game->ray_ang) > 0)
		cpy_y -= 1.;
	if (!horiz && cos(game->ray_ang) <= 0)
		cpy_x -= 1;
	if (cpy_y < 0. || cpy_x < 0.)
		return (0);
	map_y = (long)(cpy_y / IMG_SIZE);
	if (map_y >= game->parsing->len_y)
		return (0);
	len = (int)ft_strlen(game->parsing->map[map_y]);
	if (game->parsing->map[map_y] && (long)(cpy_x / IMG_SIZE) <= len)
	{
		if (game->parsing->map[map_y][(long)(cpy_x / IMG_SIZE)] == '1')
			return (0);
	}
	return (1);
}

double	get_distance(t_game *game, t_coor *inter)
{
	double	a;
	double	b;

	a = game->play_x - inter->x;
	b = game->play_y - inter->y;
	return (sqrt(pow(a, 2) + pow(b, 2)));
}

static void	check_each_inter(t_game *game, t_coor *inter, t_coor *step, int h)
{
	while (check_wall(game, inter, h))
	{
		inter->x += step->x;
		inter->y += step->y;
	}
	if (inter->x < 0)
		inter->x = 0;
	if (inter->y < 0)
		inter->y = 0;
}

double	get_horiz_inter(t_game *game, double curr_ang, double s)
{
	t_coor	step;
	t_coor	inter;
	double	t;

	t = tan(curr_ang);
	inter.y = (int)(game->play_y / IMG_SIZE) * IMG_SIZE;
	if (s > 0)
		inter.x = game->play_x + ((game->play_y - inter.y) / t);
	else
	{
		inter.y += IMG_SIZE;
		inter.x = game->play_x + ((game->play_y - inter.y) / t);
	}
	step.y = IMG_SIZE;
	if (s > 0)
		step.y *= -1;
	step.x = IMG_SIZE / t;
	eval_step(curr_ang, &step.x, 1);
	check_each_inter(game, &inter, &step, 1);
	return (get_distance(game, &inter));
}

double	get_verti_inter(t_game *game, double curr_ang, double c)
{
	t_coor	step;
	t_coor	inter;
	double	t;

	t = tan(curr_ang);
	inter.x = (int)(game->play_x / IMG_SIZE) * IMG_SIZE;
	if (c <= 0)
		inter.y = game->play_y + ((game->play_x - inter.x) * t);
	else
	{
		inter.x += IMG_SIZE;
		inter.y = game->play_y + ((game->play_x - inter.x) * t);
	}
	step.x = IMG_SIZE;
	if (c < 0)
		step.x *= -1;
	step.y = IMG_SIZE * t;
	eval_step(curr_ang, &step.y, 0);
	check_each_inter(game, &inter, &step, 0);
	return (get_distance(game, &inter));
}
