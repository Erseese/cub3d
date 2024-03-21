/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsuc <bsuc@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 09:13:35 by ytouihar          #+#    #+#             */
/*   Updated: 2024/03/19 16:04:01 by bsuc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	file_len(t_file *file)
{
	int	i;

	i = 0;
	if (file == NULL)
		return (i);
	while (file)
	{
		i++;
		file = file->next;
	}
	return (i);
}

void	empty_init(t_file *init)
{
	if (trim_backslashn(init) == 1)
	{
		ft_putstr_fd(RED BOLD "Error\n" RESET, 2);
		ft_putstr_fd("Empty file or gnl() failed\n", 2);
		exit(0);
	}
	if (ft_inisize(init) < 9)
	{
		free_struct(init);
		errorfunctionparse(NULL, "File too small\n");
	}
}

int	check_border(char **copy_map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (handle_right(copy_map) == 1)
		return (free_map(copy_map), 1);
	while (copy_map[++j + 1] != NULL)
		if (check_correct_walls(copy_map, j, 0, LEFT) == 1)
			return (free_map(copy_map), 1);
	while (copy_map[0][++i + 1] != '\n')
		if (check_correct_walls(copy_map, 0, i, UP) == 1)
			return (free_map(copy_map), 1);
	i = 0;
	while (copy_map[j][++i + 1] != '\0')
		if (check_correct_walls(copy_map, j, i, DOWN) == 1)
			return (free_map(copy_map), 1);
	return (free_map(copy_map), 0);
}

int	line_copy(t_data *d, int i, int j, char **map)
{
	while (++d->index < i - 1)
	{
		d->index_j = 0;
		d->copy_map[d->index] = malloc((j + 2) * sizeof(char));
		if (d->copy_map[d->index] == NULL)
		{
			free_map(d->copy_map);
			return (1);
		}
		while (map[d->index][d->index_j] != '\n' && map[d->index][d->index_j])
		{
			d->copy_map[d->index][d->index_j] = map[d->index][d->index_j];
			d->index_j++;
		}
		d->index_j--;
		while (++d->index_j < j)
			d->copy_map[d->index][d->index_j] = ' ';
		d->copy_map[d->index][d->index_j] = '\n';
		d->copy_map[d->index][d->index_j + 1] = '\0';
	}
	return (0);
}
