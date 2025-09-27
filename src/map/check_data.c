/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nitadros <nitadros@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 23:50:56 by nitadros          #+#    #+#             */
/*   Updated: 2025/09/26 21:51:41 by nitadros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static int	check_xpm(t_data *d)
{
	return (d->map.textures.ea.addr
		&& d->map.textures.so.addr
		&& d->map.textures.we.addr
		&& d->map.textures.no.addr);
}

int	check_data(t_data *d, char *filename)
{
	if (!parse_file(d, filename))
		return (0);
	if (!check_xpm(d))
		return (0);
	if (!check_map_data(*d) ||!check_param(*d))
		return (0);
	return (1);
}
