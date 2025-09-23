/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nitadros <nitadros@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 02:09:52 by nitadros          #+#    #+#             */
/*   Updated: 2025/09/23 16:20:20 by nitadros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static void	parse_param_utils(t_data *d, char *trimed, char **param)
{
	if (!ft_strncmp(param[0], "NO", 2))
		handle_no_so(d, trimed, 1);
	else if (!ft_strncmp(param[0], "SO", 2))
		handle_no_so(d, trimed, 2);
	else if (!ft_strncmp(param[0], "WE", 2))
		handle_we_ea(d, trimed, 1);
	else if (!ft_strncmp(param[0], "EA", 2))
		handle_we_ea(d, trimed, 2);
	fulfill_fc(param, d);
}

static void	parse_param(t_data *d, char *line)
{
	char	**param;
	char	**fc;
	char	*trimed;

	param = NULL;
	fc = NULL;
	trimed = NULL;
	if (!line)
		return ;
	param = ft_split(line, 32);
	if (!param)
		return ;
	if (param[1])
		trimed = remove_spaces(param[1]);
	parse_param_utils(d, trimed, param);
	if (param)
		ft_free_split(param);
	if (trimed)
		free(trimed);
}

static char	*parse_map(t_data *d, char *line, int *i)
{
	char	*trimed;

	trimed = ft_strtrim(line, "\n");
	if (trimed[0] != 0)
	{
		d->map.map[(*i)++] = ft_strdup(trimed);
	}
	free(trimed);
	free(line);
	line = get_next_line(d->map.fd_file);
	return (line);
}

int	parse_file(t_data *d, char *filename)
{
	int		i;
	char	*line;
	char	*trimed;

	i = 0;
	trimed = NULL;
	d->map.fd_file = open(filename, O_RDONLY);
	if (d->map.fd_file == -1)
		return (0);
	line = get_next_line(d->map.fd_file);
	if (!line)
		return (0);
	while (line)
	{
		while (line[i] == ' ' || line[i] == '\t')
			i++;
		if (!ft_strncmp(&line[i], "1", 1) || !ft_strncmp(&line[i], "0", 1))
			break ;
		parse_param(d, line);
		free(line);
		line = get_next_line(d->map.fd_file);
	}
	i = 0;
	while (line && ft_strncmp(line, "\n", 1))
		line = parse_map(d, line, &i);
	while (line)
	{
		line = parse_map(d, line, &i);
		if (line && ft_strncmp(line, "\n", 1))
			return (d->map.map[i] = NULL, free(line), 0);
	}
	d->map.map[i] = NULL;
	if (!normalize_map(d))
		return (0);
	return (free(line), 1);
}
