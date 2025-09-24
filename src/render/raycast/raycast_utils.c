/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nitadros <nitadros@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 00:53:40 by nitadros          #+#    #+#             */
/*   Updated: 2025/09/25 01:00:23 by nitadros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	check_side2(t_raydata *rd, t_raycast *raycast,
	t_data *data, t_direction **tex)
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
	rd->drawStart = (data->mlx.height - rd->lineHeight) / 2;
	rd->drawEnd = rd->drawStart + rd->lineHeight - 1;
	if (rd->drawStart < 0)
		rd->drawStart = 0;
	if (rd->drawEnd >= data->mlx.height)
		rd->drawEnd = data->mlx.height - 1;
	rd->ceil_col = rgb24(data->map.textures.fc[0]);
	rd->floor_col = rgb24(data->map.textures.fc[1]);
}

void	init_tex_and_draw(t_raycast *raycast,
	t_raydata *rd, t_direction *tex, t_data *d)
{
	char	*p;

	p = NULL;
	if (raycast->side <= 1)
		rd->wallX = raycast->posY + rd->dist * raycast->rayDirY;
	else
		rd->wallX = raycast->posX + rd->dist * raycast->rayDirX;
	rd->wallX -= floor(rd->wallX);
	rd->texX = (int)(rd->wallX * tex->width);
	rd->step = (double)tex->height / (double)rd->lineHeight;
	rd->texPos = (rd->drawStart - d->mlx.height / 2.0
			+ rd->lineHeight / 2.0) * rd->step;
	rd->y = 0;
	while (rd->y < rd->drawStart)
	{
		p = rd->addr + (rd->y * rd->line_len + rd->x * (rd->bpp / 8));
		*(unsigned int *)p = rd->ceil_col;
		rd->y++;
	}
}

void	draw_wall(t_raydata *rd, t_data *data, t_direction *tex)
{
	unsigned int	color;
	char			*src;
	int				texy;
	char			*p;

	src = NULL;
	p = NULL;
	rd->y = rd->drawStart;
	while (rd->y <= rd->drawEnd)
	{
		texy = (int)rd->texPos;
		if (texy < 0)
			texy = 0;
		if (texy >= tex->height)
			texy = tex->height - 1;
		rd->texPos += rd->step;
		src = tex->addr + texy * tex->line_len + rd->texX * (tex->bpp / 8);
		color = *(unsigned int *)src;
		p = rd->addr + (rd->y * rd->line_len + rd->x * (rd->bpp / 8));
		*(unsigned int *)p = color;
		rd->y++;
	}
}

void	draw_floor_and_put_screen(t_raydata *rd,
	t_raycast *raycast, t_data *data)
{
	char	*p;

	p = NULL;
	rd->y = rd->drawEnd + 1;
	while (rd->y < data->mlx.height)
	{
		p = rd->addr + (rd->y * rd->line_len + rd->x * (rd->bpp / 8));
		*(unsigned int *)p = rd->floor_col;
		rd->y++;
	}
	rd->hitX = raycast->posX + raycast->rayDirX * rd->finalDist;
	rd->hitY = raycast->posY + raycast->rayDirY * rd->finalDist;
	draw_line(raycast, data, rd);
	rd->x++;
}

void	all_checks(t_raycast *raycast,
	t_raydata *rd, t_data *data, t_direction *tex)
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
