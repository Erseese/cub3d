/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_struct.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 15:26:25 by ytouihar          #+#    #+#             */
/*   Updated: 2024/03/21 14:30:47 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_file	*lstlast(t_file *lst)
{
	if (lst == NULL)
		return (lst);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

static t_file	*lstnew(char *line)
{
	t_file	*stru;

	stru = (t_file *)malloc(sizeof(t_file));
	if (stru == NULL)
		return (NULL);
	stru->line = line;
	stru->next = NULL;
	return (stru);
}

static void	lstadd_back(t_file **lst, t_file *new)
{
	t_file	*pointer;

	if (lst == NULL || new == NULL)
		return ;
	pointer = *lst;
	if (*lst == NULL)
		(*lst) = new;
	else
	{
		pointer = lstlast(*lst);
		pointer->next = new;
	}
}

void	get_cubfile(t_file **init, char *file)
{
	int		fd;
	t_file	*new;
	char	*line;

	fd = open(file, O_RDONLY);
	line = get_next_line(fd);
	while (line && line[0] == '\n')
		line = get_next_line(fd);
	while (line)
	{
		new = lstnew(line);
		lstadd_back(init, new);
		line = get_next_line(fd);
	}
	if (errno != 0)
	{
		free_struct(*init);
		ft_putstr_fd(RED BOLD "Error\n" RESET, 2);
		ft_putstr_fd("get_next_line() failed\n", 2);
		exit(EXIT_FAILURE);
	}
}
