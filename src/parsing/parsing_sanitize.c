/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_sanitize.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytouihar <ytouihar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 21:05:18 by marvin            #+#    #+#             */
/*   Updated: 2024/03/21 18:30:38 by ytouihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_struct(t_file *init)
{
	t_file	*tmp;

	if (init == NULL)
		return ;
	while (init->next)
	{
		tmp = init->next;
		if (init->line)
			free(init->line);
		free(init);
		init = tmp;
	}
	if (init->line)
		free(init->line);
	free(init);
}

void	errorfunctionparse(t_parse *parsed, char *message)
{
	int	i;

	i = -1;
	if (parsed != NULL)
	{
		free_struct(parsed->init);
		free(parsed->north);
		free(parsed->south);
		free(parsed->east);
		free(parsed->west);
		if (parsed->map)
		{
			while (parsed->map[++i])
				free(parsed->map[i]);
			free(parsed->map);
		}
		free(parsed);
	}
	ft_putstr_fd(RED BOLD "Error\n" RESET, 2);
	ft_putstr_fd(message, 2);
	exit(EXIT_FAILURE);
}

void	free_map(char **map)
{
	int	i;

	i = 0;
	if (map)
	{
		while (map[i])
		{
			free(map[i]);
			i++;
		}
		free(map);
	}
}

void	free_parse(t_parse *parsed)
{
	free(parsed->north);
	free(parsed->south);
	free(parsed->east);
	free(parsed->west);
	free_map(parsed->map);
	free_map(parsed->map_copy);
	free(parsed);
	parsed = 0;
}
