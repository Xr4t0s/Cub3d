/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_screen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nitadros <nitadros@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 00:54:39 by nitadros          #+#    #+#             */
/*   Updated: 2025/09/21 02:15:21 by nitadros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int handle_mouse(int x, int y, t_data *data)
{
	int diff;
	if (data->move.m < 0)
		mlx_mouse_hide(data->mlx.mlx, data->mlx.win);
	else
		mlx_mouse_show(data->mlx.mlx, data->mlx.win);
	if (x != data->mouse.prev_x && x != data->mlx.width / 2 && data->move.m < 0)
	{
		diff = x - data->mouse.prev_x;
		data->player.angle += diff * 0.0015;
		mlx_mouse_move(data->mlx.mlx, data->mlx.win, data->mlx.width / 2, data->mlx.height / 2);
		data->mouse.prev_x = data->mlx.width / 2;
	}
	return (1);
}

void screen(t_data *data)
{
	mlx_hook(data->mlx.win, 06, 1L<<6, handle_mouse, data);
}
