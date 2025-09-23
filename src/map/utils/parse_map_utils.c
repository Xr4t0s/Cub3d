/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nitadros <nitadros@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 08:04:33 by nitadros          #+#    #+#             */
/*   Updated: 2025/09/23 18:49:31 by nitadros         ###   ########.fr       */
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

static void	establish_map_size(t_data *d)
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

int	normalize_map(t_data *d)
{
	int		i;
	int		j;
	char	**copy;
	int		count;

	establish_map_size(d);
	count = 0;
	copy = malloc(sizeof(char *) * (d->map.height + 1));
	if (!copy)
		return (0);
	i = 0;
	while (d->map.map[i])
	{
		j = 0;
		copy[i] = malloc(sizeof(char) * (d->map.width + 1));
		if (!copy[i])
		{
			ft_free_split(copy);
			return (0);
		}
		while (d->map.map[i][j])
		{
			if (d->map.map[i][j] == ' ' || d->map.map[i][j] == '\t')
				copy[i][j] = '.';
			else
				copy[i][j] = d->map.map[i][j];
			if (d->map.map[i][j] == 'S' || d->map.map[i][j] == 'N'
				|| d->map.map[i][j] == 'E' || d->map.map[i][j] == 'W')
			{
				count++;
				if (count > 1)
					return (copy[i + 1] = NULL, ft_free_split(copy), 0);
				d->player.x = j;
				d->player.xP = d->player.x * d->scale + 4;
				d->player.y = i;
				d->player.yP = d->player.y * d->scale + 4;
				if (d->map.map[i][j] == 'S')
					d->player.angle = 1.57;
				if (d->map.map[i][j] == 'E')
					d->player.angle = 0;
				if (d->map.map[i][j] == 'N')
					d->player.angle = 4.71;
				if (d->map.map[i][j] == 'W')
					d->player.angle = 3.14;
			}
			j++;
		}
		while (j < d->map.width)
			copy[i][j++] = '.';
		copy[i][j] = 0;
		i++;
	}
	copy[i] = NULL;
	if (count == 0)
		return (ft_free_split(copy), 0);
	ft_free_split(d->map.map);
	d->map.map = copy;
	return (1);
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
		no->img = mlx_xpm_file_to_image(
				d->mlx.mlx,
				trimed,
				&no->width,
				&no->height);
		no->addr = mlx_get_data_addr(no->img, &no->bpp,
				&no->line_len, &no->endian);
	}
	else
	{
		so->img = mlx_xpm_file_to_image(
				d->mlx.mlx,
				trimed,
				&so->width,
				&so->height);
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
		we->img = mlx_xpm_file_to_image(
				d->mlx.mlx,
				trimed,
				&we->width,
				&we->height);
		we->addr = mlx_get_data_addr(we->img, &we->bpp,
				&we->line_len, &we->endian);
	}
	else
	{
		ea->img = mlx_xpm_file_to_image(
				d->mlx.mlx,
				trimed,
				&ea->width,
				&ea->height);
		ea->addr = mlx_get_data_addr(ea->img, &ea->bpp,
				&ea->line_len, &ea->endian);
		printf("bpp = %d\n", ea->bpp);
	}
}
