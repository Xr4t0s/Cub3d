/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rayscast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nitadros <nitadros@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 00:17:11 by engiacom          #+#    #+#             */
/*   Updated: 2025/09/24 23:34:11 by nitadros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"
#include "raycast.h"
#include <math.h>

#define MAX_DIST 15.0

void	draw_line(char *addr, int x0, int y0, int x1, int y1, int color, int bpp, int line_len)
{
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;

	dx = abs(x1 - x0);
	dy = abs(y1 - y0);
	err = dx - dy;
	if (x0 < x1)
		sx = 1;
	else
		sx = -1;
	if (y0 < y1)
		sy = 1;
	else
		sy = -1;
	while (1)
	{
		if (x0 >= 0 && y0 >= 0)
		{
			char *pixel = addr + (y0 * line_len + x0 * (bpp / 8));
			*(unsigned int *)pixel = color;
		}
		if (x0 == x1 && y0 == y1)
			break;
		int e2 = 2 * err;
		if (e2 > -dy)
		{
			err -= dy;
			x0 += sx;
		}
		if (e2 < dx)
		{
			err += dx;
			y0 += sy;
		}
	}
}

void	init_ray(t_raydata *rd, t_data *data)
{
	handle_keypress(0, data);
	
	if (rd->img == NULL)
	{
		rd->img = mlx_new_image(data->mlx.mlx, data->mlx.width, data->mlx.height);
		rd->addr = mlx_get_data_addr(rd->img, &rd->bpp, &rd->line_len, &rd->endian);
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
	raycast->planeY =  raycast->dirX * tan(data->player.fov / 2);
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
		raycast->sideDistX = (raycast->posX - raycast->mapX) * raycast->deltaDistX;
	else
		raycast->sideDistX = (raycast->mapX + 1.0 - raycast->posX) * raycast->deltaDistX;
	if (raycast->rayDirY < 0)
		raycast->sideDistY = (raycast->posY - raycast->mapY) * raycast->deltaDistY;
	else
		raycast->sideDistY = (raycast->mapY + 1.0 - raycast->posY) * raycast->deltaDistY;
}

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
			raycast->perpWallDist =
				(raycast->mapX - raycast->posX + (1 - raycast->stepX) / 2.0) / raycast->rayDirX;
		}
		else
		{
			raycast->perpWallDist =
				(raycast->mapY - raycast->posY + (1 - raycast->stepY) / 2.0) / raycast->rayDirY;
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

void	check_side2(t_raydata *rd, t_raycast *raycast, t_data *data, t_direction **tex)
{
	(void)tex;
	if (rd->hit)
		rd->dist = raycast->perpWallDist;
	else
		rd->dist = 1e9;
	if (rd->dist > 0.0)
		rd->lineHeight = (int)(data->mlx.height / rd->dist);
	else
		rd->lineHeight = data->mlx.height;
	rd->drawStart  = (data->mlx.height - rd->lineHeight) / 2;
	rd->drawEnd    = rd->drawStart + rd->lineHeight - 1;
	if (rd->drawStart < 0)
		rd->drawStart = 0;
	if (rd->drawEnd >= data->mlx.height)
		rd->drawEnd = data->mlx.height - 1;
	rd->ceil_col  = rgb24(data->map.textures.fc[0]);
	rd->floor_col = rgb24(data->map.textures.fc[1]);
	
}

void	init_tex_and_draw(t_raycast *raycast, t_raydata *rd, t_direction *tex, t_data *d)
{
	if (raycast->side <= 1)
		rd->wallX = raycast->posY + rd->dist * raycast->rayDirY;
	else
		rd->wallX = raycast->posX + rd->dist * raycast->rayDirX;
	rd->wallX -= floor(rd->wallX);
	
	rd->texX = (int)(rd->wallX * tex->width);
	rd->step = (double)tex->height / (double)rd->lineHeight;
	rd->texPos = (rd->drawStart - d->mlx.height /2.0 + rd->lineHeight / 2.0) * rd->step;

	rd->y = 0;
	while (rd->y < rd->drawStart)
	{
		char *p = rd->addr + (rd->y * rd->line_len + rd->x * (rd->bpp / 8));
		*(unsigned int *)p = rd->ceil_col;
		rd->y++;
	}
}

void	draw_wall(t_raydata *rd, t_data *data, t_direction *tex)
{
	rd->y = rd->drawStart;
	while (rd->y <= rd->drawEnd)
	{
		unsigned int color;
		int texY = (int)rd->texPos;
		
		if (texY < 0) texY = 0;
		if (texY >= tex->height) texY = tex->height - 1;
		rd->texPos += rd->step;
		char *src = tex->addr + texY * tex->line_len + rd->texX * (tex->bpp/8);
		color = *(unsigned int*)src;
		char *p = rd->addr + (rd->y * rd->line_len + rd->x * (rd->bpp / 8));
		*(unsigned int *)p = color;
		rd->y++;
	}
}

void	draw_floor_and_put_screen(t_raydata *rd, t_raycast *raycast, t_data *data)
{
	rd->y = rd->drawEnd + 1;
	while (rd->y < data->mlx.height)
	{
		char *p = rd->addr + (rd->y * rd->line_len + rd->x * (rd->bpp / 8));
		*(unsigned int *)p = rd->floor_col;
		rd->y++;
	}
	rd->hitX = raycast->posX + raycast->rayDirX * rd->finalDist;
	rd->hitY = raycast->posY + raycast->rayDirY * rd->finalDist;
	draw_line(
		rd->addr,
		(int)(raycast->posX * data->scale + 1.5), (int)(raycast->posY * data->scale),
		(int)(rd->hitX * data->scale),               (int)(rd->hitY * data->scale),
		0x00FFFF00, rd->bpp, rd->line_len
	);
	rd->x++;
}

void all_checks(t_raycast *raycast, t_raydata *rd, t_data *data, t_direction *tex)
{
	tex = NULL;
	base_calc(raycast, data, rd);
	base_calc2(raycast);
	rd->hit = 0;
	rd->distance_travelled = 0.0f;
	while (rd->hit == 0 && rd->distance_travelled < MAX_DIST)
	{
		ray_check(raycast, rd, data);
		ray_check2(raycast, rd, data);
		ray_check3(raycast);

	}
	check_side(rd, raycast);
	check_side2(rd, raycast, data, &tex);
}

int	render(void *param)
{
	t_data	*data = (t_data *)param;
	t_raydata	rd;
	t_direction *tex;
	static t_raycast raycast;

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
	data->raycast.door = -1;
	minimap(data, rd.addr, rd.bpp, rd.line_len);
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.win, rd.img, 0, 0);
	mlx_destroy_image(data->mlx.mlx, rd.img);
	return (0);
}
