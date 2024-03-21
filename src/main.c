/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytouihar <ytouihar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 17:19:43 by bsuc              #+#    #+#             */
/*   Updated: 2024/03/21 18:32:23 by ytouihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int ac, char **av)
{
	t_parse	*pars;
	t_game	game;

	if (ac != 2)
	{
		ft_putstr_fd(RED BOLD "Error\n" RESET "Not enough arguments\n", 2);
		return (1);
	}
	pars = parsing(av);
	if (parsing_map(pars))
		return (free_parse(pars), 1);
	pars->map_copy = map_copy(pars->map);
	pars->len_y = ft_strlen_matrice(pars->map);
	game_init(&game, pars);
	govalo(&game);
	mlx_hook(game.win, KeyPress, KeyPressMask, get_key_event, &game);
	//mlx_mouse_hook(game.win, mouse_hook, &game);	
	//mlx_hook(game.win, 06, 1L << 6, game_mouse_move, &game);
	mlx_hook(game.win, DestroyNotify, 0, win_exit, &game);
	mlx_loop_hook(game.mlx, &render, &game);
	mlx_loop(game.mlx);
	return (0);
}
