/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init_doors_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytouihar <ytouihar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 17:35:27 by ytouihar          #+#    #+#             */
/*   Updated: 2024/03/21 18:05:22 by ytouihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	tree_doors(t_door **doors, int y, int x)
{
	t_door	*door;
	t_door	*ptr;

	door = malloc(sizeof(t_door));
	door->startx = x;
	door->starty = 1 + y;
	door->endx = x + 1;
	door->endy = y + 1;
	door->px = door->startx * 64;
	door->py = door->starty * 64 + 32;
	door->endpx = door->endx * 64;
	door->endpy = door->endy * 64 + 32;
	door->time = get_current_time(0);
	door->open = 0;
	door->next = NULL;
	if (*doors == NULL)
	{
		*doors = door;
		return ;
	}
	ptr = (*doors);
	while (ptr != NULL && ptr->next)
		ptr = ptr->next;
	if (ptr != NULL)
		ptr->next = door;
}

void	govalo(t_game *game)
{
	int	y;
	int	x;

	y = 0;
	while (game->parsing->map[y])
	{
		x = 0;
		while (game->parsing->map[y][x])
		{
			if (game->parsing->map[y][x] == 'D')
				tree_doors(&game->doors, y, x);
			x++;
		}
		y++;
	}
}
