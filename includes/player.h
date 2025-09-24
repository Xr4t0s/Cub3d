/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engiacom <engiacom@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 06:38:38 by nitadros          #+#    #+#             */
/*   Updated: 2025/09/25 00:59:49 by engiacom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H
# include "cube3d.h"

typedef struct s_player
{
	int		x;
	int		y;
	double	xP;
	double	yP;
	double	angle;
	double	fov;
	double	fov_rot;
	double	rot;
	double	move_speed;
}	t_player;

#endif