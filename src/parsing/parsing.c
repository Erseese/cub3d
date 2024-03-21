/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytouihar <ytouihar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 14:00:46 by ytouihar          #+#    #+#             */
/*   Updated: 2024/03/21 18:29:50 by ytouihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	check_inside_char(t_parse *parse)
{
	if (parse->north[0] == '\0')
	{
		ft_putstr_fd(RED BOLD "Error\n" RESET "file empty north\n", 2);
		exit(EXIT_FAILURE);
		free_parse(parse);
	}
	if (parse->south[0] == '\0')
	{
		ft_putstr_fd(RED BOLD "Error\n" RESET "file empty south\n", 2);
		exit(EXIT_FAILURE);
		free_parse(parse);
	}
	if (parse->west[0] == '\0')
	{
		ft_putstr_fd(RED BOLD "Error\n" RESET "file empty west\n", 2);
		exit(EXIT_FAILURE);
		free_parse(parse);
	}
	if (parse->east[0] == '\0')
	{
		ft_putstr_fd(RED BOLD "Error\n" RESET "file empty east\n", 2);
		exit(EXIT_FAILURE);
		free_parse(parse);
	}
}

int	trim_backslashn(t_file *init)
{
	t_file	*blsm;
	t_file	*tmp;

	blsm = init;
	if (!blsm)
		return (1);
	if (!blsm->next)
	{
		free(blsm->line);
		free(blsm);
		return (1);
	}
	while (blsm->next && blsm->line[0] != '1')
	{
		if (blsm->next->line[0] == '\n')
		{
			free(blsm->next->line);
			tmp = blsm->next->next;
			free(blsm->next);
			blsm->next = tmp;
		}
		else
			blsm = blsm->next;
	}
	return (0);
}

static void	check_file(char *file)
{
	char	*ext;
	size_t	len;

	ext = ft_strrchr(file, '.');
	if (ext == 0)
	{
		ft_putstr_fd(RED BOLD "Error\n" RESET "Wrong filename\n", 2);
		exit(EXIT_FAILURE);
	}
	len = ft_strlen(ext);
	if (len < 4)
		len = 4;
	if (!ext || ft_strncmp(ext, ".cub", len) != 0 || len == 0)
	{
		ft_putstr_fd(RED BOLD "Error\n" RESET "Wrong filename\n", 2);
		exit(EXIT_FAILURE);
	}
}

t_parse	*parsing(char **argv)
{
	t_file	*init;
	t_parse	*parsed;

	init = 0;
	check_file(argv[1]);
	get_cubfile(&init, argv[1]);
	empty_init(init);
	parsed = initalizeparse();
	if (parsed == NULL)
	{
		free_struct(init);
		errorfunctionparse(NULL, "Malloc error\n");
	}
	fill_struct(parsed, init);
	free_struct(init);
	check_inside_char(parsed);
	return (parsed);
}
