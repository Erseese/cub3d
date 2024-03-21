/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pistol_utils_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytouihar <ytouihar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 17:05:59 by ytouihar          #+#    #+#             */
/*   Updated: 2024/03/21 17:04:25 by ytouihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	hit_enemy(t_game *game, t_coor inter)
{
	int	map_y;

	map_y = (int)(inter.y / 64.);
	if (game->parsing->map[map_y][(int)(inter.x / 64.)] == '1' \
	|| game->parsing->map[map_y][(int)(inter.x / 64.)] == 'D')
		return (0);
	if (game->parsing->map[map_y][(int)(inter.x / 64.)] == 'n')
	{
		game->parsing->map[map_y][(int)(inter.x / 64.)] = '0';
		return (2);
	}
	return (1);
}

static int	check_enemy(t_game *game, t_coor inter, int inters)
{
	int	len;

	if (inters == 2)
		inter.y -= 1;
	if (inter.y < 0 || inter.x < 0)
		return (0);
	if ((inter.y / IMG_SIZE) > game->parsing->len_y)
		return (0);
	if (game->parsing->map[(int)(inter.y / IMG_SIZE)] != NULL)
		len = (int)ft_strlen(game->parsing->map[(int)(inter.y / IMG_SIZE)]);
	else
		len = 0;
	if ((int)(inter.x / 64.) < 0)
		return (0);
	if (game->parsing->map[(int)(inter.y / 64.)] && (int)(inter.x / 64.) <= len)
		return (hit_enemy(game, inter));
	return (1);
}

int	find_enemy(t_game *game, t_coor step, t_coor pos_ray, int test)
{
	int	aim;

	aim = check_enemy(game, pos_ray, test);
	while (aim == 1)
	{
		pos_ray.x += step.x;
		pos_ray.y += step.y;
		aim = check_enemy(game, pos_ray, test);
	}
	return (aim);
}
