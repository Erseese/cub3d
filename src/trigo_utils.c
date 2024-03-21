/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trigo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 14:58:23 by marvin            #+#    #+#             */
/*   Updated: 2024/03/17 15:08:04 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	eval_move(t_game *game, t_coor *move, int dir)
{
	double	s;

	s = sin(game->play_ang);
	if (dir)
	{
		if (s > 0 && move->x < 0)
			move->x *= -1;
		if (s < 0 && move->x > 0)
			move->x *= -1;
	}
	else
	{
		if (s > 0 && move->x > 0)
			move->x *= -1;
		if (s < 0 && move->x < 0)
			move->x *= -1;
	}
}

void	eval_step(double curr_ang, double *step, int x)
{
	double	c;
	double	s;

	if (x)
	{
		c = cos(curr_ang);
		if (c >= 0 && *step < 0)
			*step *= -1;
		if (c < 0 && *step > 0)
			*step *= -1;
	}
	else
	{
		s = sin(curr_ang);
		if (s >= 0 && *step > 0)
			*step *= -1;
		if (s < 0 && *step < 0)
			*step *= -1;
	}
}

void	check_max_trigo(double ang)
{
	if (ang <= 0)
		ang += M_PI * 2;
	if (ang >= M_PI * 2)
		ang -= M_PI * 2;
}
