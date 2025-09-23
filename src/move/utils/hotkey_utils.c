/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nitadros <nitadros@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 18:02:45 by nitadros          #+#    #+#             */
/*   Updated: 2025/09/23 18:38:47 by nitadros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static void	init_angle_data(t_tmp_angle *tmp, t_data *data)
{
	tmp->x = data->player.xP;
	tmp->y = data->player.yP;
	tmp->angle = data->player.angle;
	tmp->xtestpos = data->map.map[(int)tmp->y / data->scale]
	[(int)(tmp->x + 1) / data->scale];
	tmp->xtestneg = data->map.map[(int)tmp->y / data->scale]
	[(int)(tmp->x - 1) / data->scale];
	tmp->ytestpos = data->map.map[(int)(tmp->y + 1) / data->scale]
	[(int)tmp->x / data->scale];
	tmp->ytestneg = data->map.map[(int)(tmp->y - 1) / data->scale]
	[(int)tmp->x / data->scale];
}

int	check_angle(t_data *data)
{
	t_tmp_angle	tmp;

	init_angle_data(&tmp, data);
	if (tmp.angle >= 0 && tmp.angle <= 1.57)
	{
		if (tmp.xtestpos == '1' && tmp.ytestpos)
			return (0);
	}
	else if (tmp.angle >= 1.57 && tmp.angle <= 3.14)
	{
		if (tmp.xtestneg == '1' && tmp.ytestpos == '1')
			return (0);
	}
	else if (tmp.angle >= 3.14 && tmp.angle <= 4.71)
	{
		if (tmp.xtestneg == '1' && tmp.ytestneg)
			return (0);
	}
	else if (tmp.angle >= 4.71 && tmp.angle <= 6.28)
	{
		if (tmp.xtestpos == '1' && tmp.ytestneg)
			return (0);
	}
	return (1);
}
