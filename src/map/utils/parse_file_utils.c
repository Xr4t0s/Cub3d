/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nitadros <nitadros@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 15:56:16 by nitadros          #+#    #+#             */
/*   Updated: 2025/09/25 20:55:52 by nitadros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	check_img(char *filename, t_data *d)
{
	void	*img;
	int		x;
	int		y;

	img = NULL;
	img = mlx_xpm_file_to_image(d->mlx.mlx, filename, &x, &y);
	if (!img)
		return (0);
	return (mlx_destroy_image(d->mlx.mlx, img), 1);
}

int	fulfill_fc(char **param, t_data *d)
{
	char	**fc;

	if (!ft_strncmp(param[0], "C", 1))
	{
		fc = ft_split(param[1], ',');
		if (!fc || (!fc[0] || !fc[1] || !fc[2]))
			return (ft_free_split(fc), 0);
		d->map.textures.fc[0][0] = ft_atoi(fc[0]);
		d->map.textures.fc[0][1] = ft_atoi(fc[1]);
		d->map.textures.fc[0][2] = ft_atoi(fc[2]);
		ft_free_split(fc);
	}
	if (!ft_strncmp(param[0], "F", 1))
	{
		fc = ft_split(param[1], ',');
		if (!fc || (!fc[0] || !fc[1] || !fc[2]))
			return (ft_free_split(fc), 0);
		d->map.textures.fc[1][0] = ft_atoi(fc[0]);
		d->map.textures.fc[1][1] = ft_atoi(fc[1]);
		d->map.textures.fc[1][2] = ft_atoi(fc[2]);
		ft_free_split(fc);
	}
	return (1);
}
