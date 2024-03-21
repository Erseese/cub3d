/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_doors_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytouihar <ytouihar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 17:38:17 by ytouihar          #+#    #+#             */
/*   Updated: 2024/03/21 17:42:18 by ytouihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	middle_door(t_game *game, int *x, int *y)
{
	if (game->curr_ang > 0 && game->curr_ang < M_PI)
	{
		*y += 1;
		*x += 32 / tan(game->curr_ang);
		*y += -32 + 64;
	}
	else
	{
		*y += 64;
		*x += -32 / tan(game->curr_ang);
		*y += 32 + 64;
	}
}

static int	pos_door(t_game *game, int x, int y)
{
	t_door	*tmp;

	tmp = game->doors;
	middle_door(game, &x, &y);
	if (tmp == NULL)
		return (0);
	while (tmp)
	{
		if (game->curr_ang > 0 && game->curr_ang < M_PI)
		{
			if (x >= tmp->px && x <= tmp->endpx && y == tmp->py)
				return (1);
		}
		else
			if (x >= tmp->px && x <= tmp->endpx && y == tmp->py + 64)
				return (1);
		tmp = tmp->next;
	}
	return (0);
}

static int	check_door(t_game *game, t_coor inter, int inters)
{
	int	len;
	int	map_y;

	if (inters == 2)
		inter.y -= 1;
	map_y = (int)(inter.y / 64.);
	if (inter.y < 0 || inter.x < 0)
		return (2);
	if ((inter.y / IMG_SIZE) > game->parsing->len_y)
		return (2);
	if (game->parsing->map[(int)(inter.y / IMG_SIZE)] != NULL)
		len = (int)ft_strlen(game->parsing->map[map_y]);
	else
		len = 0;
	if ((int)(inter.x / 64.) < 0)
		return (2);
	if (game->parsing->map[map_y] && (int)(inter.x / 64.) <= len)
	{
		if (game->parsing->map[map_y][(int)(inter.x / 64.)] == '1')
			return (2);
		if (game->parsing->map[map_y][(int)(inter.x / 64.)] == 'D' \
		&& pos_door(game, inter.x, inter.y) == 1)
			return (0);
	}
	return (1);
}

static void	add_distance(t_game *game, t_coor *pos_ray)
{
	if (game->curr_ang > 0 && game->curr_ang < M_PI)
	{
		pos_ray->x += 32. / tan(game->curr_ang);
		pos_ray->y += -32;
	}
	else
	{
		pos_ray->x += -32. / tan(game->curr_ang);
		pos_ray->y += 32;
	}
}

int	find_door(t_game *game, t_coor step, t_coor *pos_ray, int test)
{
	int	test2;

	test2 = check_door(game, *pos_ray, test);
	while (test2 == 1)
	{
		pos_ray->x += step.x;
		pos_ray->y += step.y;
		test2 = check_door(game, *pos_ray, test);
	}
	if (test2 == 2)
		return (-1);
	add_distance(game, pos_ray);
	return (0);
}
