/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engiacom <engiacom@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 20:51:52 by engiacom          #+#    #+#             */
/*   Updated: 2025/09/25 00:53:43 by engiacom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIMAP_H
# define MINIMAP_H

# include "cube3d.h"

typedef struct s_minivar
{
	char	*addr;
	int		x;
	int		y;
	int		px;
	int		py;
	int		color;
	int		bpp;
	int		line_len;

}	t_minivar;

void	minimap_draw_pixel(t_minivar *mini, int x, int y, t_data *data);

#endif