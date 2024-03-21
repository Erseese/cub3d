/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_wall.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsuc <bsuc@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 15:58:07 by marvin            #+#    #+#             */
/*   Updated: 2024/03/19 17:15:54 by bsuc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	hit_wall_x(t_game *game, double move_x)
{
	int	map_x;

	if (fabs(move_x) < 0.000001)
	map_x = (int)((game->play_x + move_x) / IMG_SIZE);
	else if (move_x > 0.)
		map_x = (int)((game->play_x + move_x /*+ PLAYER_WIDTH*/) / IMG_SIZE);
	else
		map_x = (int)((game->play_x + move_x /*- PLAYER_WIDTH*/) / IMG_SIZE);
	return (map_x);
}

static int	hit_wall_y(t_game *game, double move_y)
{
	int	map_y;
	if (fabs(move_y) < 0.000001)
	map_y = (int)((game->play_y + move_y) / IMG_SIZE);
	else if (move_y > 0.)
		map_y = (int)((game->play_y + move_y /*+ PLAYER_WIDTH*/) / IMG_SIZE);
	else
		map_y = (int)((game->play_y + move_y /*- PLAYER_WIDTH*/) / IMG_SIZE);
	return (map_y);
}


int	hit_wall(t_game *game, t_coor *move)
{
	int	map_x;
	int	map_y;

	map_x = hit_wall_x(game, move->x);
	map_y = hit_wall_y(game, move->y);
	if (game->parsing->map[map_y][map_x] == '1')
		return (1);
	return (0);
}
