/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nitadros <nitadros@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 06:38:38 by nitadros          #+#    #+#             */
/*   Updated: 2025/09/25 12:51:05 by nitadros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H
# include "cube3d.h"

typedef struct s_player
{
	int		x;
	int		y;
	double	xp;
	double	yp;
	double	angle;
	double	fov;
	double	fov_rot;
	double	rot;
	double	move_speed;
}	t_player;

#endif