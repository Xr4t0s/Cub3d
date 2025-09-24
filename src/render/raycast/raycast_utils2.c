/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nitadros <nitadros@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 00:53:40 by nitadros          #+#    #+#             */
/*   Updated: 2025/09/25 01:00:16 by nitadros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	ray_check(t_raycast *raycast, t_raydata *rd, t_data *data)
{
	if (raycast->sideDistX < raycast->sideDistY)
	{
		rd->distance_travelled = raycast->sideDistX;
		raycast->sideDistX += raycast->deltaDistX;
		raycast->mapX += raycast->stepX;
		raycast->side = 0;
	}
	else
	{
		rd->distance_travelled = raycast->sideDistY;
		raycast->sideDistY += raycast->deltaDistY;
		raycast->mapY += raycast->stepY;
		raycast->side = 2;
	}
	if (data->map.map[raycast->mapY][raycast->mapX] == '1'
		|| data->map.map[raycast->mapY][raycast->mapX] == 'D')
		rd->hit = 1;
}

void	ray_check2(t_raycast *raycast, t_raydata *rd, t_data *data)
{
	if (data->map.map[raycast->mapY][raycast->mapX] == 'D'
		&& data->raycast.door > 0 && (fabs(raycast->sideDistX) <= 2
		|| fabs(raycast->sideDistY) <= 2) && raycast->cameraX >= -0.30
		&& raycast->cameraX <= 0.30)
	{
		data->map.map[raycast->mapY][raycast->mapX] = '*';
		data->raycast.door *= -1;
		rd->hit = 0;
	}
	else if (data->map.map[raycast->mapY][raycast->mapX] == '*'
		&& data->raycast.door > 0 && (fabs(raycast->sideDistX) <= 2
		|| fabs(raycast->sideDistY) <= 2) && raycast->cameraX >= -0.30
		&& raycast->cameraX <= 0.30)
	{
		data->map.map[raycast->mapY][raycast->mapX] = 'D';
		data->raycast.door *= -1;
		rd->hit = 1;
	}
}

void	ray_check3(t_raycast *raycast)
{
	if (raycast->side == 2)
	{
		if (raycast->posY > raycast->mapY)
			raycast->side = 3;
	}
	else
	{
		if (raycast->posX > raycast->mapX)
			raycast->side = 1;
	}
}

void	check_side(t_raydata *rd, t_raycast *raycast)
{
	rd->hitX = raycast->posX + raycast->sideDistX * raycast->rayDirX;
	rd->hitY = raycast->posY + raycast->sideDistY * raycast->rayDirY;
	if (rd->hit)
	{
		if (raycast->side <= 1)
		{
			raycast->perpWallDist = (raycast->mapX - raycast->posX
					+ (1 - raycast->stepX) / 2.0) / raycast->rayDirX;
		}
		else
		{
			raycast->perpWallDist = (raycast->mapY - raycast->posY
					+ (1 - raycast->stepY) / 2.0) / raycast->rayDirY;
		}
		if (raycast->perpWallDist < MAX_DIST)
			rd->finalDist = raycast->perpWallDist;
		else
			rd->finalDist = MAX_DIST;
	}
	else
	{
		rd->finalDist = MAX_DIST;
	}
}
