/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytouihar <ytouihar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 10:28:17 by ytouihar          #+#    #+#             */
/*   Updated: 2024/03/21 18:34:25 by ytouihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_empty(char c)
{
	if (c && c != ' ' && c != '1' && c != '\n')
		return (1);
	return (0);
}

static int	check_corner(char **map, int i, int j)
{
	int	maxj;

	maxj = ft_strlen(map[i]);
	if (i + 1 < ft_strlen_matrice(map) && j - 1 > 0)
		if (is_empty(map[i + 1][j - 1]))
			return (1);
	if (i - 1 > 0 && j + 1 < maxj)
		if (is_empty(map[i - 1][j + 1]))
			return (1);
	if (j + 1 < maxj && i + 1 < ft_strlen_matrice(map))
		if (is_empty(map[i + 1][j + 1]))
			return (1);
	if (j - 1 > 0 && i - 1 > 0)
		if (is_empty(map[i - 1][j - 1]))
			return (1);
	return (0);
}

static int	check_space_inside(char **map, int i, int j)
{
	int	maxj;

	maxj = ft_strlen(map[i]);
	if (i + 1 < ft_strlen_matrice(map))
		if (is_empty(map[i + 1][j]))
			return (1);
	if (i - 1 > 0)
		if (is_empty(map[i - 1][j]))
			return (1);
	if (j + 1 < maxj)
		if (is_empty(map[i][j + 1]))
			return (1);
	if (j - 1 > 0)
		if (is_empty(map[i][j - 1]))
			return (1);
	if (check_corner(map, i, j) == 1)
		return (1);
	return (0);
}

static int	check_pos(char c, t_parse *parsed)
{
	if (c == 'N' && parsed->player_position == 0)
		parsed->player_position = NORTH;
	else if (c == 'S' && parsed->player_position == 0)
		parsed->player_position = SOUTH;
	else if (c == 'E' && parsed->player_position == 0)
		parsed->player_position = EAST;
	else if (c == 'W' && parsed->player_position == 0)
		parsed->player_position = WEST;
	else if (c != '\0' && c != '1' && c != '0' && c != '\n' && c != ' ' \
	 && c != 'D' && c != 'n')
		return (1);
	return (0);
}

int	check_inside(t_parse *parsed, char **copy_map)
{
	int		i;
	int		j;

	i = 0;
	if (copy_map == NULL || copy_map[0] == NULL)
		return (1);
	while (copy_map[i])
	{
		j = 0;
		while (copy_map[i][j])
		{
			if (check_pos(copy_map[i][j], parsed) != 0)
				return (free_map(copy_map), 1);
			if (copy_map[i][j] == ' ')
				if (check_space_inside(copy_map, i, j) == 1)
					return (free_map(copy_map), 2);
			j++;
		}
		i++;
	}
	return (0);
}
