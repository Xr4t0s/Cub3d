/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nitadros <nitadros@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 06:37:41 by nitadros          #+#    #+#             */
/*   Updated: 2025/09/23 18:51:50 by nitadros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	main(int ac, char **av)
{
	t_data	data;

	if (ac != 2)
		return (printf("Error bad arguments"), 1);
	data.mlx.mlx = mlx_init();
	if (!data.mlx.mlx)
		return (0);
	init(&data);
	if (!check_data(&data, av[1]))
		return (free_all(&data, 0),
			printf("error"), 0);
	data.mlx.win = mlx_new_window(data.mlx.mlx, data.mlx.width,
			data.mlx.height, "Hello");
	movements(&data);
	screen(&data);
	mlx_loop_hook(data.mlx.mlx, render, &data);
	mlx_loop(data.mlx.mlx);
	free_all(&data, 1);
}
