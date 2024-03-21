/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   right_side.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsuc <bsuc@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 19:25:43 by ytouihar          #+#    #+#             */
/*   Updated: 2024/03/19 16:04:28 by bsuc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	find_longest_line(char **map, int *i)
{
	int	j;
	int	compteur;

	compteur = 0;
	j = 0;
	while (map[*i])
	{
		j = 0;
		while (map[*i][j] != '\n' && map[*i][j] != '\0')
			j++;
		if (compteur < j)
			compteur = j;
		*i = *i + 1;
	}
	return (compteur);
}

static void	last_line_copy(t_data *d, int index, char **map, int j)
{
	int	index_j;

	index_j = -1;
	d->copy_map[index] = malloc((1 + j) * sizeof(char));
	if (d->copy_map[index] == NULL)
	{
		free_map(d->copy_map);
		d->copy_map = NULL;
		return ;
	}
	while (map[index][++index_j] != '\n' && map[index][index_j])
		d->copy_map[index][index_j] = map[index][index_j];
	while (index_j < j)
	{
		d->copy_map[index][index_j] = ' ';
		index_j++;
	}
	d->copy_map[index][index_j] = 0;
}

char	**copy_right_with_spaces(char **map, int i, int j)
{
	t_data	d;

	ft_memset(&d, 0, sizeof(d));
	d.index = -1;
	d.copy_map = malloc(sizeof(char *) * (i + 1));
	if (d.copy_map == NULL)
		return (NULL);
	d.copy_map[i] = NULL;
	if (line_copy(&d, i, j, map))
		return (NULL);
	last_line_copy(&d, d.index, map, j);
	return (d.copy_map);
}

int	handle_right(char **copy_map)
{
	int		i;

	i = 1;
	if (copy_map == NULL || copy_map[0] == NULL)
		return (1);
	while (copy_map[i + 1] && copy_map[i])
	{
		if (copy_map[i][ft_strlen(copy_map[i]) - 1] == ' ')
		{
			if (check_correct_walls(copy_map, i, \
			ft_strlen(copy_map[i]) - 2, RIGHT) == 1)
				return (1);
		}
		i++;
	}
	return (0);
}
