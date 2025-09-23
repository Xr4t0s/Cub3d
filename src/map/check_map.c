/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nitadros <nitadros@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 06:54:02 by nitadros          #+#    #+#             */
/*   Updated: 2025/09/23 18:44:43 by nitadros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static int	flood_check(char **map, int i, int j)
{
	if (i < 0 || j < 0 || map[i] == NULL || map[i][j] == '\0')
		return (0);
	if (map[i][j] == '.' || map[i][j] == ' ')
		return (0);
	if (map[i][j] == '1' || map[i][j] == '*')
		return (1);
	map[i][j] = '*';
	return (flood_check(map, i + 1, j)
		&& flood_check(map, i - 1, j)
		&& flood_check(map, i, j + 1)
		&& flood_check(map, i, j - 1)
	);
}

int	check_map_data(t_data d)
{
	char	**copy;

	copy = ft_tabdup(d.map.map);
	if (!copy)
		return (printf("Failed to duplicate the map for checking\n"), 0);
	if (!flood_check(copy, d.player.y, d.player.x))
		return (ft_free_split(copy), 0);
	return (ft_free_split(copy), 1);
}
