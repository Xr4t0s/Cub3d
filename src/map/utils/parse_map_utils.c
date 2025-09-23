/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nitadros <nitadros@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 08:04:33 by nitadros          #+#    #+#             */
/*   Updated: 2025/09/23 21:53:55 by nitadros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

char	*remove_spaces(char *line)
{
	int		i;
	int		j;
	char	*clean;

	i = 0;
	j = 0;
	clean = malloc(ft_strlen(line) + 1);
	while (line[i])
	{
		while (!ft_strncmp(&line[i], " ", 1) || !ft_strncmp(&line[i], "\n", 1))
			i++;
		if (!line[i])
			break ;
		clean[j++] = line[i++];
	}
	clean[j] = 0;
	return (clean);
}

void	establish_map_size(t_data *d)
{
	int		i;
	int		j;
	int		max_width;

	i = 0;
	j = 0;
	max_width = 0;
	while (d->map.map[i])
	{
		while (d->map.map[i][j])
			j++;
		if (j > max_width)
			max_width = j;
		j = 0;
		i++;
	}
	d->map.height = i;
	d->map.width = max_width;
}

void	handle_no_so(t_data *d, char *trimed, int target)
{
	t_direction	*no;
	t_direction	*so;
	int			fd;

	no = &d->map.textures.no;
	so = &d->map.textures.so;
	fd = open(trimed, O_RDONLY);
	if (fd == -1)
		return ;
	close(fd);
	if (target == 1)
	{
		no->img = mlx_xpm_file_to_image(d->mlx.mlx, trimed,
				&no->width, &no->height);
		no->addr = mlx_get_data_addr(no->img, &no->bpp,
				&no->line_len, &no->endian);
	}
	else
	{
		so->img = mlx_xpm_file_to_image(d->mlx.mlx, trimed,
				&so->width, &so->height);
		so->addr = mlx_get_data_addr(so->img, &so->bpp,
				&so->line_len, &so->endian);
	}
}

void	handle_we_ea(t_data *d, char *trimed, int target)
{
	t_direction	*we;
	t_direction	*ea;
	int			fd;

	we = &d->map.textures.we;
	ea = &d->map.textures.ea;
	fd = open(trimed, O_RDONLY);
	if (fd == -1)
		return ;
	close(fd);
	if (target == 1)
	{
		we->img = mlx_xpm_file_to_image(d->mlx.mlx, trimed,
				&we->width, &we->height);
		we->addr = mlx_get_data_addr(we->img, &we->bpp,
				&we->line_len, &we->endian);
	}
	else
	{
		ea->img = mlx_xpm_file_to_image(d->mlx.mlx, trimed,
				&ea->width, &ea->height);
		ea->addr = mlx_get_data_addr(ea->img, &ea->bpp,
				&ea->line_len, &ea->endian);
		printf("bpp = %d\n", ea->bpp);
	}
}
