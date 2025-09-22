/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nitadros <nitadros@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 00:52:48 by nitadros          #+#    #+#             */
/*   Updated: 2025/09/22 22:50:11 by nitadros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "free.h"

static void	free_textures(t_data *d)
{
	// if (d->minimap.player)
	// 	mlx_destroy_image((*d).mlx.mlx, (*d).minimap.player);
	// if (d->minimap.bg)
	// 	mlx_destroy_image((*d).mlx.mlx, (*d).minimap.bg);
	// if (d->minimap.bg4)
	// 	mlx_destroy_image((*d).mlx.mlx, (*d).minimap.bg4);
	// if (d->minimap.wall)
	// 	mlx_destroy_image((*d).mlx.mlx, (*d).minimap.wall);
}

static void	free_directions(t_data *d)
{
	if (d->map.textures.no.img)
		mlx_destroy_image((*d).mlx.mlx, (*d).map.textures.no.img);
	if (d->map.textures.so.img)
		mlx_destroy_image((*d).mlx.mlx, (*d).map.textures.so.img);
	if (d->map.textures.we.img)
		mlx_destroy_image((*d).mlx.mlx, (*d).map.textures.we.img);
	if (d->map.textures.ea.img)
		mlx_destroy_image((*d).mlx.mlx, (*d).map.textures.ea.img);
}

void	free_all(t_data *d, int x)
{
	if (d->map.map)
		ft_free_split(d->map.map);
	free_directions(d);
	free_textures(d);
	if (x == 1)
	{
		if (d->mlx.mlx)
			mlx_loop_end(d->mlx.mlx);
		if (!d->mlx.win)
			mlx_destroy_window(d->mlx.mlx, d->mlx.win);
		if (!d->mlx.mlx)
			mlx_destroy_display(d->mlx.mlx);
	}
	free(d->mlx.mlx);
}
