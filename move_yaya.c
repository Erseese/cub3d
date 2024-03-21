/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_yaya.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 16:34:32 by bsuc              #+#    #+#             */
/*   Updated: 2024/03/21 14:43:38 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// void	eval_move(t_game *game, t_coor *move, int dir)
// {
// 	if (dir)
// 	{
// 		if (game->play_ang > 0 && game->play_ang < M_PI && move->x < 0)
// 			move->x *= -1;
// 		if (game->play_ang > M_PI && game->play_ang < M_PI * 2 && move->x > 0)
// 			move->x *= -1;
// 	}
// 	else
// 	{
// 		if (game->play_ang > 0 && game->play_ang < M_PI && move->x > 0)
// 			move->x *= -1;
// 		if (game->play_ang > M_PI && game->play_ang < M_PI * 2 && move->x < 0)
// 			move->x *= -1;
// 	}
// }

void	move_player(t_game *game, t_coor *move, int key)
{
	if (key == XK_d)
	{
		move->x = -sin(game->play_ang) * PLAYER_SPEED;
		move->y = cos(game->play_ang) * PLAYER_SPEED;
		eval_move(game, move, 1);
	}
	if (key == XK_a)
	{
		move->x = sin(game->play_ang) * PLAYER_SPEED;
		move->y = -cos(game->play_ang) * PLAYER_SPEED;
		eval_move(game, move, 0);
	}
	if (key == XK_w)
	{
		move->x = cos(game->play_ang) * PLAYER_SPEED;
		move->y = -sin(game->play_ang) * PLAYER_SPEED;
	}
	if (key == XK_s)
	{
		move->x = -cos(game->play_ang) * PLAYER_SPEED;
		move->y = sin(game->play_ang) * PLAYER_SPEED;
	}
}

void	smoothing(int smoothing, int delay, int x, int y, t_game *game)
{
	for (int i = 0; i < smoothing; i++)
	{
		game->play_x += x / smoothing;
		game->play_y += y / smoothing;
		usleep(delay / smoothing); // Utilisez usleep pour le délai
	}
	game->play_x += x % smoothing;
	game->play_y += y % smoothing;
	usleep(delay % smoothing);
}

int is_in_square(t_game game, t_coor startp, t_coor endp) {
	int dx;
	int dy;
	int stepSize;
	int stepX;
	int stepY;
	int	i;
	
	dx = endp.x - startp.x;
	i = -1;
	dy = endp.y - startp.y;
	stepSize = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
	stepX = dx > 0 ? 1 : -1;
	stepY = dy > 0 ? 1 : -1;
	while (++i <= stepSize)
	{
		if (game.parsing->map[(int)startp.y / 64][(int)startp.x / 64] == '1' \
		|| game.parsing->map[(int)startp.y / 64][(int)startp.x / 64] == 'D')
			return (1);
		startp.x += stepX;
		startp.y += stepY;
	}
	return (0);
}

int	testthings(t_coor move, t_coor startp, t_coor endp, t_game game)
{
	int	test = 0;
	int	count = 0;
	int negatifx = 1;
	int	negatify = 1;

	if ((int)fabs(move.x) > (int)fabs(move.y))
		test = (int)fabs(move.x) - (int)fabs(move.y);
	else
		test = (int)fabs(move.y) - (int)fabs(move.x);
	if (move.x > 0)
		negatifx = -1;
	else 
		negatifx = 1;
	if (move.y > 0)
		negatify = -1;
	else 
		negatify = 1;
	while ((int)move.x != 0 || (int)move.y != 0)
	{
		if (test == 0 && count == 0)
		{
			startp.x -= negatifx;
			endp.x -= negatifx;
			move.x += negatifx;
			count++;
		}
		if (test == 0 && count == 1)
		{
			startp.y -= negatify;
			endp.y -= negatify;
			move.y += negatify;
			count = 0;
		}
		if (count < test && (int)fabs(move.x) > (int)fabs(move.y))
		{
			startp.x -= negatifx;
			endp.x -= negatifx;
			move.x += negatifx;
			count++;
		}
		else if ((count < test && (int)fabs(move.x) <= (int)fabs(move.y)))
		{
			startp.y -= negatify;
			endp.y -= negatify;
			move.y += negatify;
			count++;
		}
		else if (test != 0 && (count >= test && (int)fabs(move.x) > (int)fabs(move.y)))
		{
			startp.y -= negatify;
			endp.y -= negatify;
			move.y += negatify;
			count = 0;
		}
		else if (test != 0 && (count >= test && (int)fabs(move.x) <= (int)fabs(move.y)))
		{
			startp.x -= negatifx;
			endp.x -= negatifx;
			move.x += negatifx;
			count = 0;
		}
		if (is_in_square(game, startp, endp) == 1)
			return (1);
	}
	return (0);
}

void	key_move(t_game *game, int keycode)
{
	t_coor	move;
	t_coor	startp;
	t_coor	endp;

	move.x = 0;
	move.y = 0;
	startp.x = game->play_x - 2;
	startp.y = game->play_y - 2;
	endp.x = game->play_x + 2;
	endp.y = game->play_y + 2;
	move_player(game, &move, keycode);
	if (testthings(move, startp, endp, *game) == 0)
		smoothing(10, 10000, move.x, move.y, game);
}

int	get_key_event(int keycode, t_game *game)
{
	// printf("click :%d\n", keycode);
	if (keycode == XK_Escape)
		win_exit(game);
	if (keycode == XK_Left)
	{
		game->play_ang += (M_PI * 2 / 180);
		if (game->play_ang >= M_PI * 2)
			game->play_ang -= M_PI * 2;
	}
	if (keycode == XK_Right)
	{
		game->play_ang -= (M_PI * 2 / 180);
		if (game->play_ang <= 0)
			game->play_ang += M_PI * 2;
	}
	if (keycode == XK_w || keycode == XK_d || keycode == XK_s || keycode == XK_a)
		key_move(game, keycode);
	//if (keycode ==)
	//if (keycode == XK_Control_L)
		//mlx_mouse_show(game->mlx, game->win);
	//if (keycode == XK_Control_R)
		//mlx_mouse_hide(game->mlx, game->win);
	// if (keycode == XK_e)
	// 	open_door(game);
	return (0);
}
