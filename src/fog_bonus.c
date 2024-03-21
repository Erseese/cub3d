/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fog_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytouihar <ytouihar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 17:43:07 by ytouihar          #+#    #+#             */
/*   Updated: 2024/03/21 18:09:38 by ytouihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

unsigned int	colorize(unsigned int color, double fog)
{
	t_color	c1;
	t_color	c2;
	t_color	c3;

	c1.t = (color >> 24) & 0xFF;
	c1.r = (color >> 16) & 0xFF;
	c1.g = (color >> 8) & 0xFF;
	c1.b = color & 0xFF;
	c3.t = (0 >> 24) & 0xFF;
	c3.r = (0 >> 16) & 0xFF;
	c3.g = (0 >> 8) & 0xFF;
	c3.b = 0 & 0xFF;
	c2.t = (unsigned int)(c1.t * (1.0 - fog) + c3.t * fog);
	c2.r = (unsigned int)(c1.r * (1.0 - fog) + c3.r * fog);
	c2.g = (unsigned int)(c1.g * (1.0 - fog) + c3.g * fog);
	c2.b = (unsigned int)(c1.b * (1.0 - fog) + c3.b * fog);
	return (c2.t << 24 | c2.r << 16 | c2.g << 8 | c2.b);
}
