/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pistol_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytouihar <ytouihar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 18:27:00 by ytouihar          #+#    #+#             */
/*   Updated: 2024/03/21 17:54:21 by ytouihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_pas_mes_ennemis(t_game *game)
{
	if (game->parsing->map[(int)(game->play_y / 64)] \
	[(int)(game->play_x / 64)] == 'n')
		exit(1);
}

static double	shoot(t_game *game, double curr_ang)
{
	t_coor	step;
	t_coor	pos_ray;
	int		test;

	test = -1;
	if (curr_ang > 0 && curr_ang < M_PI)
	{
		pos_ray.y = (int)(game->play_y / IMG_SIZE) * IMG_SIZE;
		test = 2;
	}
	else
	{
		pos_ray.y = (int)(game->play_y / IMG_SIZE) * IMG_SIZE + 64.;
	}
	pos_ray.x = game->play_x + (game->play_y - pos_ray.y) / tan(curr_ang);
	step.y = IMG_SIZE;
	if (curr_ang > 0 && curr_ang < M_PI)
		step.y *= -1;
	step.x = IMG_SIZE / tan(curr_ang);
	eval_step(curr_ang, &step.x, 1);
	return (find_enemy(game, step, pos_ray, test));
}

void	cursor(t_game *game)
{
	int	i;
	int	j;

	i = -5;
	j = -5;
	while (i <= 5)
	{
		j = -5;
		while (j <= 5)
		{
			if (((j > -2 && j < 2) || (i > -2 && i < 2)))
			{
				if (!((j > -2 && j < 2) && (i > -2 && i < 2)))
				{
					my_mlx_pixel_put(&game->img, \
					CENTER_W + i, CENTER_H + j, 0xff11b2);
				}
			}
			j++;
		}
		i++;
	}
}

int	mouse_hook(int button, int x, int y, t_game *game)
{
	double	angle;

	angle = game->curr_ang;
	if (button == 1)
		shoot(game, angle);
	return (0);
}

void	pistol(t_game *game)
{
	int		i;
	int		j;
	int		color;

	i = 0;
	while (i < PistolW)
	{
		j = 0;
		while (j < PistolH)
		{
			color = pixel_get(&game->pistol, i, j);
			if (color != -16777216)
			{
				my_mlx_pixel_put(&game->img, CENTER_W + i - 99 / 2, \
				(WIN_HEIGHT - PistolH + 2) + j, color);
			}
			j++;
		}
		i++;
	}
}
