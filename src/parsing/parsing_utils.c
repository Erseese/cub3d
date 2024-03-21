/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsuc <bsuc@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 18:45:38 by ytouihar          #+#    #+#             */
/*   Updated: 2024/03/19 16:03:42 by bsuc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_end_parse(t_parse *parsed, t_file *init, int index)
{
	int	count;

	count = 0;
	while (init->line[index] != '\n')
	{
		if (count >= 3)
			errorfunctionparse(parsed, "Wrong color or ceiling\n");
		if (ft_isdigit(init->line[index]) == 0 && init->line[index] != '\n')
			errorfunctionparse(parsed, "Wrong color or ceiling\n");
		count++;
		index++;
	}
}

int	ft_inisize(t_file *lst)
{
	int	compteur;

	compteur = 0;
	while (lst != NULL)
	{
		compteur++;
		lst = lst->next;
	}
	return (compteur);
}

int	ft_strlen_matrice(char **map)
{
	int	len;

	len = 0;
	while (map[len])
		len++;
	return (len);
}

int	skip_nb_and_spaces(int index, t_parse *parsed, t_file *init)
{
	int	tmp;

	tmp = index;
	while (init->line[index] && init->line[index] != ',' && \
	ft_isdigit(init->line[index]))
		index++;
	if (index - tmp >= 4 || (ft_isdigit(init->line[index]) == 0 && \
	init->line[index] != ','))
		errorfunctionparse(parsed, "Wrong rgb code\n");
	index++;
	while (init->line[index] && init->line[index] == ' ')
		index++;
	return (index);
}

t_parse	*initalizeparse(void)
{
	t_parse	*parsed;

	parsed = malloc(sizeof(t_parse));
	if (parsed == NULL)
		return (NULL);
	ft_memset(parsed, 0, sizeof(t_parse));
	parsed->f_red = 0;
	parsed->f_green = 0;
	parsed->f_blue = 0;
	parsed->c_red = 0;
	parsed->c_green = 0;
	parsed->c_blue = 0;
	parsed->player_position = 0;
	return (parsed);
}
