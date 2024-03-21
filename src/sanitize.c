/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sanitize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytouihar <ytouihar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 18:09:56 by bsuc              #+#    #+#             */
/*   Updated: 2024/03/21 16:42:27 by ytouihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_ptr(t_game *game)
{
	if (game->text[0].img)
		mlx_destroy_image(game->mlx, game->text[0].img);
	if (game->text[1].img)
		mlx_destroy_image(game->mlx, game->text[1].img);
	if (game->text[2].img)
		mlx_destroy_image(game->mlx, game->text[2].img);
	if (game->text[3].img)
		mlx_destroy_image(game->mlx, game->text[3].img);
	if (game->door.img)
		mlx_destroy_image(game->mlx, game->door.img);
	if (game->pistol.img)
		mlx_destroy_image(game->mlx, game->pistol.img);
}

void	handle_error(const char *s, t_parse *parsing, int ex)
{
	ft_putstr_fd(RED BOLD "[Error]\n" RESET, 2);
	if (s)
		ft_putstr_fd((char *)s, 2);
	if (parsing)
		free_parse(parsing);
	if (ex)
		exit(EXIT_FAILURE);
}

int	win_exit(t_game *game)
{
	if (game->img.img)
		mlx_destroy_image(game->mlx, game->img.img);
	free_ptr(game);
	mlx_destroy_window(game->mlx, game->win);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	if (game->parsing)
		free_parse(game->parsing);
	exit(EXIT_SUCCESS);
	return (0);
}
