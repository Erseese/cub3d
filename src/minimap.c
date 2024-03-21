/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytouihar <ytouihar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 17:06:26 by ytouihar          #+#    #+#             */
/*   Updated: 2024/03/21 18:39:45 by ytouihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_circle(t_game *game)
{
	unsigned short int	i;
	unsigned short int	j;

	i = 0;
	while (i < 4 * 4)
	{
		j = 0;
		while (j < 4 * 4)
		{
			if (((j - 4) * (j - 4)) + ((i - 4) * (i - 4)) < (4 * 4))
			{
				my_mlx_pixel_put(&game->img, \
				j + game->minimap_size / 2 - 4, \
				i + game->minimap_size / 2 - 4, 0xf1445);
			}
			j++;
		}
		i++;
	}
}

static int	color_choosing(int posx, int posy, char **map, t_game *game)
{
	int	len_max_mapx;
	int	len_max_mapy;
	int	x;
	int	y;

	x = roundf(posx);
	y = roundf(posy);
	len_max_mapx = ft_strlen(map[0]);
	len_max_mapy = ft_strlen_matrice(map);
	if (len_max_mapx <= x)
		return (1);
	if (0 > x)
		return (1);
	if (len_max_mapy <= y)
		return (1);
	if (0 > y)
		return (1);
	if (map[y][x] == '1' || map[y][x] == ' ')
		return (1);
	if (map[y][x] == 'D')
		return (2);
	if (map[y][x] == '0')
		return (0);
	return (0);
}

static void	player_vision(double x, double y, t_game *game, double number_ray)
{
	double	nbr_pixel;
	double	ray_x;
	double	ray_y;
	double	mapy;
	double	mapx;

	nbr_pixel = 0;
	ray_x = nbr_pixel * (cos(game->ray_ang + number_ray));
	ray_y = nbr_pixel * (-sin(game->ray_ang + number_ray));
	mapy = (game->play_y / 64.0) + ((ray_y) / ((double)WIN_HEIGHT / 54.));
	mapx = (game->play_x / 64.0) + ((ray_x) / ((double)WIN_HEIGHT / 54.));
	while (game->parsing->map[(int)(mapy)][(int)(mapx)] != '1' \
	&& game->parsing->map[(int)(mapy)][(int)(mapx)] != 'D' \
		&& ceil(x + ray_x) < game->minimap_size \
		&& ceil(y + ray_y) < game->minimap_size \
		&& x + ray_x > 0 \
		&& y + ray_y > 0)
	{
		ray_x = nbr_pixel * (cos(game->ray_ang + number_ray));
		ray_y = nbr_pixel * (-sin(game->ray_ang + number_ray));
		mapy = (game->play_y / 64.0) + ((ray_y) / ((double)WIN_HEIGHT / 54.));
		mapx = (game->play_x / 64.0) + ((ray_x) / ((double)WIN_HEIGHT / 54.));
		my_mlx_pixel_put(&game->img, x + ray_x, y + ray_y, 0x987456);
		nbr_pixel++;
	}
}

static void	print_layout(t_game *game, double posx, double posy, char **map)
{
	int		x;
	int		color;
	int		y;
	double	pxl_x;
	double	pxl_y;

	y = 0;
	while (y < game->minimap_size)
	{	
		x = 0;
		while (x < game->minimap_size)
		{
			pxl_x = (double)x / (((double)game->minimap_size / MINIMAP_BLOCK));
			pxl_y = (double)y / (((double)game->minimap_size / MINIMAP_BLOCK));
			color = color_choosing((posx + pxl_x), (posy + pxl_y), map, game);
			if (color == 1)
				my_mlx_pixel_put(&game->img, x, y, 0x000000);
			else if (color == 0)
				my_mlx_pixel_put(&game->img, x, y, 0xffffff);
			else
				my_mlx_pixel_put(&game->img, x, y, 0xff0000);
			x++;
		}
		y++;
	}
}

void	minimap(char **map, t_game *game)
{
	double	posx;
	double	posy;
	double	i;

	posx = (double)game->play_x / IMG_SIZE - 4.5;
	posy = (double)game->play_y / IMG_SIZE - 4.5;
	print_layout(game, posx, posy, map);
	i = 0;
	while (i < FOV_RAD)
	{
		player_vision(game->minimap_size / 2 + 1, \
		game->minimap_size / 2 + 1, game, i);
		i += 0.01;
	}
	draw_circle(game);
}
