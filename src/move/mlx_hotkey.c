/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_hotkey.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nitadros <nitadros@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 23:17:57 by engiacom          #+#    #+#             */
/*   Updated: 2025/09/23 18:42:58 by nitadros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"
#include "raycast.h"

int	go_up(t_data *d)
{
	t_tmpvar	tmp;

	tmp.ny = sin(d->player.angle) * 3;
	tmp.yP1 = d->player.yP + tmp.ny;
	tmp.nx = cos(d->player.angle) * 3;
	tmp.xP1 = d->player.xP + tmp.nx;
	tmp.first = d->map.map[tmp.yP1 / d->scale][(int)d->player.xP / d->scale];
	tmp.secnd = d->map.map[(int)d->player.yP / d->scale][tmp.xP1 / d->scale];
	if (!check_angle(d))
		return (0);
	if (tmp.first != '1' && tmp.first != 'D')
	{
		d->player.yP += sin(d->player.angle) * d->player.move_speed;
		d->player.y = d->player.yP / d->scale;
	}
	if (tmp.secnd != '1' && tmp.secnd != 'D')
	{
		d->player.xP += cos(d->player.angle) * d->player.move_speed;
		d->player.x = d->player.xP / d->scale;
	}
	return (1);
}

int	go_down(t_data *d)
{
	t_tmpvar	tmp;

	tmp.ny = sin(d->player.angle) * 3;
	tmp.yP1 = d->player.yP - tmp.ny;
	tmp.nx = cos(d->player.angle) * 3;
	tmp.xP1 = d->player.xP - tmp.nx;
	tmp.first = d->map.map[tmp.yP1 / d->scale][(int)d->player.xP / d->scale];
	tmp.secnd = d->map.map[(int)d->player.yP / d->scale][tmp.xP1 / d->scale];
	if (!check_angle(d))
		return (0);
	if (tmp.first != '1' && tmp.first != 'D')
	{
		d->player.yP -= sin(d->player.angle) * d->player.move_speed;
		d->player.y = d->player.yP / d->scale;
	}
	if (tmp.secnd != '1' && tmp.secnd != 'D')
	{
		d->player.xP -= cos(d->player.angle) * d->player.move_speed;
		d->player.x = d->player.xP / d->scale;
	}
	return (1);
}

int	go_left(t_data *d)
{
	t_tmpvar	tmp;

	tmp.a = d->player.angle;
	tmp.ny = -cos(tmp.a) * 3.0;
	tmp.yP1 = d->player.yP + tmp.ny;
	tmp.nx = sin(tmp.a) * 3.0;
	tmp.xP1 = d->player.xP + tmp.nx;
	tmp.first = d->map.map[tmp.yP1 / d->scale][(int)d->player.xP / d->scale];
	tmp.secnd = d->map.map[(int)d->player.yP / d->scale][tmp.xP1 / d->scale];
	if (!check_angle(d))
		return (0);
	if (tmp.first != '1' && tmp.first != 'D')
	{
		d->player.yP += -cos(tmp.a) * (d->player.move_speed / 1.5);
		d->player.y = d->player.yP / d->scale;
	}
	if (tmp.secnd != '1' && tmp.secnd != 'D')
	{
		d->player.xP += sin(tmp.a) * (d->player.move_speed / 1.5);
		d->player.x = d->player.xP / d->scale;
	}
	return (1);
}

int	go_right(t_data *d)
{
	t_tmpvar	tmp;

	tmp.a = d->player.angle;
	tmp.ny = cos(tmp.a) * 3.0;
	tmp.yP1 = d->player.yP + tmp.ny;
	tmp.nx = -sin(tmp.a) * 3.0;
	tmp.xP1 = d->player.xP + tmp.nx;
	tmp.first = d->map.map[tmp.yP1 / d->scale][(int)d->player.xP / d->scale];
	tmp.secnd = d->map.map[(int)d->player.yP / d->scale][tmp.xP1 / d->scale];
	if (!check_angle(d))
		return (0);
	if (tmp.first != '1' && tmp.first != 'D')
	{
		d->player.yP += cos(tmp.a) * (d->player.move_speed / 1.5);
		d->player.y = d->player.yP / d->scale;
	}
	if (tmp.secnd != '1' && tmp.secnd != 'D')
	{
		d->player.xP += -sin(tmp.a) * (d->player.move_speed / 1.5);
		d->player.x = d->player.xP / d->scale;
	}
	return (1);
}

int	view_left(t_data *data)
{
	data->player.angle -= data->player.rot;
	if (data->player.angle < 0)
		data->player.angle = 6.28;
	return (1);
}

int	view_right(t_data *data)
{
	data->player.angle += data->player.rot;
	if (data->player.angle > 6.28)
		data->player.angle = 0;
	return (1);
}

int	handle_keypress(int keycode, t_data *data)
{
	if (data->move.w == 1)
		go_up(data);
	if (data->move.s == 1)
		go_down(data);
	if (data->move.a == 1)
		go_left(data);
	if (data->move.d == 1)
		go_right(data);
	if (data->move.r == 1)
		view_right(data);
	if (data->move.l == 1)
		view_left(data);
	return (1);
}

int	movements(t_data *data)
{
	mlx_hook(data->mlx.win, 2, 1L << 0, key_press, data);
	mlx_hook(data->mlx.win, 3, 1L << 1, key_release, data);
	return (1);
}
