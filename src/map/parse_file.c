/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nitadros <nitadros@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 02:09:52 by nitadros          #+#    #+#             */
/*   Updated: 2025/09/25 13:17:28 by nitadros         ###   ########.fr       */
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
	char	*trimed;

	param = NULL;
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
	if (line)
		free(line);
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

static int	parse_file_init(t_parsing *tmp, t_data *d, char *filename)
{
	tmp->i = 0;
	tmp->trimed = NULL;
	d->map.fd_file = open(filename, O_RDONLY);
	if (d->map.fd_file == -1)
		return (0);
	tmp->line = get_next_line(d->map.fd_file);
	if (!tmp->line)
		return (0);
	tmp->ft = &ft_strncmp;
	return (1);
}

int	parse_file(t_data *d, char *filename)
{
	t_parsing	t;

	if (!parse_file_init(&t, d, filename))
		return (0);
	while (t.line)
	{
		while (t.line[t.i] == ' ' || t.line[t.i] == '\t')
			t.i++;
		if (!t.ft(&t.line[t.i], "1", 1) || !t.ft(&t.line[t.i], "0", 1))
			break ;
		parse_param(d, t.line);
		t.line = get_next_line(d->map.fd_file);
	}
	t.i = 0;
	while (t.line && ft_strncmp(t.line, "\n", 1))
		t.line = parse_map(d, t.line, &t.i);
	while (t.line)
	{
		t.line = parse_map(d, t.line, &t.i);
		if (t.line && ft_strncmp(t.line, "\n", 1))
			return (d->map.map[t.i] = NULL, free(t.line), 0);
	}
	if (!normalize_map(d, t.i))
		return (0);
	return (free(t.line), 1);
}
