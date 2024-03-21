/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytouihar <ytouihar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 15:27:34 by ytouihar          #+#    #+#             */
/*   Updated: 2024/03/21 18:35:04 by ytouihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	**map_copy(char **map)
{
	char	**copy_map;
	int		i;
	int		compteur;

	i = 0;
	compteur = find_longest_line(map, &i);
	copy_map = copy_right_with_spaces(map, i, compteur);
	if (copy_map == NULL)
		return (NULL);
	return (copy_map);
}

static int	check_around(int i, int j, char **map, int type)
{
	if (map[i][j] == '\0' || map[i][j] == '0' || map[i][j] == 'N' \
	|| map[i][j] == 'S' || map[i][j] == 'W' || map[i][j] == 'E')
		return (1);
	if (type == UP || type == DOWN)
	{
		if (map[i][j + 1] != '\0' && map[i][j + 1] == '0')
			return (1);
		if (map[i][j - 1] != '\0' && map[i][j - 1] == '0')
			return (1);
	}
	else
	{
		if (map[i - 1][j] != '\0' && map[i - 1][j] == '0')
			return (1);
		if (map[i + 1][j] != '\0' && map[i + 1][j] == '0')
			return (1);
	}
	return (0);
}

static int	find_path(int i, int j, char **map, int type)
{
	int	len_max;

	len_max = ft_strlen_matrice(map);
	if (check_around(i, j, map, type))
		return (1);
	if (map[i][j] == ' ')
	{
		map[i][j] = '2';
		if (type == UP)
			if ((i + 1 > len_max) && find_path(i + 1, j, map, type))
				return (1);
		if (type == DOWN)
			if ((i - 1 < 0) && find_path(i - 1, j, map, type))
				return (1);
		if (type == LEFT)
			if (find_path(i, j + 1, map, type))
				return (1);
		if (type == RIGHT)
			if (find_path(i, j - 1, map, type))
				return (1);
	}
	return (0);
}

int	check_correct_walls(char **map, int x, int y, int type)
{
	if (type == UP && find_path(x, y, map, type) == 1)
	{
		ft_putstr_fd(RED BOLD"Error\n", 2);
		return (ft_putstr_fd("Hole in the up part of the map\n", 2), 1);
	}
	else if (type == DOWN && find_path(x, y, map, type) == 1)
	{
		ft_putstr_fd(RED BOLD"Error\n", 2);
		return (ft_putstr_fd("Hole in the down part of the map\n", 2), 1);
	}
	else if (type == RIGHT && find_path(x, y, map, type) == 1)
	{
		ft_putstr_fd(RED BOLD"Error\n", 2);
		return (ft_putstr_fd("Hole in the right part of the map\n", 2), 1);
	}
	else if (type == LEFT && find_path(x, y, map, type) == 1)
	{
		ft_putstr_fd(RED BOLD"Error\n", 2);
		return (ft_putstr_fd("Hole in the left part of the map\n", 2), 1);
	}
	return (0);
}

int	parsing_map(t_parse *parsed)
{
	char	**copy_map;
	int		error;

	copy_map = map_copy(parsed->map);
	if (copy_map == NULL || copy_map[0] == NULL)
	{
		ft_putstr_fd(RED BOLD "Error\n" RESET, 2);
		ft_putstr_fd("Malloc error\n", 2);
		return (1);
	}
	error = check_inside(parsed, copy_map);
	if (error == 1 || parsed->player_position == 0)
	{
		ft_putstr_fd(RED BOLD "Error\n" RESET, 2);
		ft_putstr_fd("Something is wrong with the player\n", 2);
		return (1);
	}
	if (error == 2)
	{
		ft_putstr_fd(RED BOLD "Error\n" RESET, 2);
		ft_putstr_fd("Something is wrong with the spaces inside the map\n", 2);
		return (1);
	}
	return (check_border(copy_map));
}
