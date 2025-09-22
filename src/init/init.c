/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nitadros <nitadros@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 00:15:14 by nitadros          #+#    #+#             */
/*   Updated: 2025/09/22 22:48:21 by nitadros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	init_map(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	map->fd_file = 0;
	map->map = malloc(sizeof(char *) * 1000);
	if (!map->map)
		return ;
	map->width = 0;
	map->height = 0;
	map->textures.no.img = NULL;
	map->textures.so.img = NULL;
	map->textures.we.img = NULL;
	map->textures.ea.img = NULL;
	while (j < 2)
	{
		while (i < 3)
		{
			map->textures.fc[j][i] = -1;
			i++;
		}
		i = 0;
		j++;
	}
}

void	init_player(t_player *player)
{
	player->x = 0;
	player->xP = 0;
	player->y = 0;
	player->yP = 0;
	player->angle = 2.355;
	player->fov = 1.1519;
	player->fov_rot = 0.05;
	player->rot = 0.05;
	player->move_speed = 1.5;
}

int	init_txt(t_data *data)
{
	// int	h;
	// int	w;
	// t_textures *t = &data->map.textures; 
	
	// t->no.img = mlx_xpm_file_to_image(data->mlx.mlx, "north.xpm", &t->no.width, &t->no.height);
	// t->so.img = mlx_xpm_file_to_image(data->mlx.mlx, "south.xpm", &t->so.width, &t->so.height);
	// t->ea.img = mlx_xpm_file_to_image(data->mlx.mlx, "east.xpm", &t->ea.width, &t->ea.height);
	// t->we.img = mlx_xpm_file_to_image(data->mlx.mlx, "west.xpm", &t->we.width, &t->we.height);
	// // if (!t->ea.img || !t->no.img || !t->so.img ||!t->we.img)
	// // 	printf("Bad text\n");
	return (1);
}

void	init_move(t_move *move)
{
	move->w = 0;
	move->a = 0;
	move->s = 0;
	move->d = 0;
	move->l = 0;
	move->r = 0;
	move->m = -1;
}

void	init_mouse(t_mouse *mouse)
{
	mouse->prev_x = 0;
}

void	init(t_data *data)
{
	data->mlx.width = 2160;
	data->mlx.height = 1440;
	init_map(&data->map);
	init_player(&data->player);
	init_txt(data);
	init_move(&data->move);
	init_mouse(&data->mouse);
	data->raycast.door = -1;
	data->scale = data->mlx.height > 1080 ? 10 : 5;
}
