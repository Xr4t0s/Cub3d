/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rayscast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nitadros <nitadros@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 00:17:11 by engiacom          #+#    #+#             */
/*   Updated: 2025/09/25 00:59:30 by nitadros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"
#include "raycast.h"
#include <math.h>

void	init_ray(t_raydata *rd, t_data *data)
{
	handle_keypress(0, data);
	if (rd->img == NULL)
	{
		rd->img = mlx_new_image(data->mlx.mlx, data->mlx.width,
				data->mlx.height);
		rd->addr = mlx_get_data_addr(rd->img, &rd->bpp,
				&rd->line_len, &rd->endian);
	}
	rd->x = 0;
}

void	base_calc(t_raycast *raycast, t_data *data, t_raydata *rd)
{
	raycast->posX = data->player.xP / data->scale;
	raycast->posY = data->player.yP / data->scale;
	raycast->dirX = cos(data->player.angle);
	raycast->dirY = sin(data->player.angle);
	raycast->planeX = -raycast->dirY * tan(data->player.fov / 2);
	raycast->planeY = raycast->dirX * tan(data->player.fov / 2);
	raycast->cameraX = 2.0f * (float)rd->x / (float)data->mlx.width - 1.0f;
	raycast->rayDirX = raycast->dirX + raycast->planeX * raycast->cameraX;
	raycast->rayDirY = raycast->dirY + raycast->planeY * raycast->cameraX;
	raycast->mapX = (int)raycast->posX;
	raycast->mapY = (int)raycast->posY;
	raycast->deltaDistX = fabs(1.0 / raycast->rayDirX);
	raycast->deltaDistY = fabs(1.0 / raycast->rayDirY);
}

void	base_calc2(t_raycast *raycast)
{
	if (raycast->rayDirX < 0)
		raycast->stepX = -1;
	else
		raycast->stepX = 1;
	if (raycast->rayDirY < 0)
		raycast->stepY = -1;
	else
		raycast->stepY = 1;
	if (raycast->rayDirX < 0)
		raycast->sideDistX = (raycast->posX - raycast->mapX)
			* raycast->deltaDistX;
	else
		raycast->sideDistX = (raycast->mapX + 1.0 - raycast->posX)
			* raycast->deltaDistX;
	if (raycast->rayDirY < 0)
		raycast->sideDistY = (raycast->posY - raycast->mapY)
			* raycast->deltaDistY;
	else
		raycast->sideDistY = (raycast->mapY + 1.0 - raycast->posY)
			* raycast->deltaDistY;
}

void	ending(t_data *data, t_raydata *rd)
{
	data->raycast.door = -1;
	minimap(data, rd->addr, rd->bpp, rd->line_len);
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.win, rd->img, 0, 0);
	mlx_destroy_image(data->mlx.mlx, rd->img);
}

int	render(void *param)
{
	t_data				*data;
	t_raydata			rd;
	t_direction			*tex;
	static t_raycast	raycast;

	data = (t_data *)param;
	rd.img = NULL;
	init_ray(&rd, data);
	while (rd.x < data->mlx.width)
	{
		all_checks(&raycast, &rd, data, tex);
		if (raycast.side == 1)
			tex = &data->map.textures.ea;
		else if (raycast.side == 2)
			tex = &data->map.textures.no;
		else if (raycast.side == 3)
			tex = &data->map.textures.so;
		else
			tex = &data->map.textures.we;
		init_tex_and_draw(&raycast, &rd, tex, data);
		draw_wall(&rd, data, tex);
		draw_floor_and_put_screen(&rd, &raycast, data);
	}
	ending(data, &rd);
	return (0);
}
