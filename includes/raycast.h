/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nitadros <nitadros@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 23:56:10 by engiacom          #+#    #+#             */
/*   Updated: 2025/09/25 01:28:10 by nitadros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCAST_H
# define RAYCAST_H
# include "cube3d.h"
# define MAX_DIST 15.0

typedef struct s_data	t_data;

typedef struct s_raycast
{
	int		mapX;
	int		mapY;
	int		stepX;
	int		stepY;
	int		hit;
	int		side;
	int		lineHeight;
	int		drawStart;
	int		drawEnd;
	int		door;
	double	posX;
	double	posY;
	double	dirX;
	double	dirY;
	double	planeX;
	double	planeY;
	double	cameraX;
	double	rayDirX;
	double	rayDirY;
	double	sideDistX;
	double	sideDistY;
	double	deltaDistX;
	double	deltaDistY;
	double	perpWallDist;
}	t_raycast;

typedef struct s_raydata
{
	int				bpp;
	int				line_len;
	int				endian;
	int				x;
	int				y;
	int				hit;
	int				lineHeight;
	int				drawStart;
	int				drawEnd;
	int				texX;
	void			*img;
	char			*addr;
	float			distance_travelled;
	float			finalDist;
	double			hitX;
	double			hitY;
	double			dist;
	double			wallX;
	double			step;
	double			texPos;
	unsigned int	ceil_col;
	unsigned int	floor_col;
}	t_raydata;

typedef struct s_draw
{
	int		x0;
	int		y0;
	int		x1;
	int		y1;
	int		dx;
	int		dy;
	int		sx;
	int		sy;
	int		err;
	int		color;
	int		e2;
	char	*pixel;
}	t_draw;

typedef struct s_minimap
{
	void	*bg;
	void	*wall;
	void	*player;
	void	*bg4;
}	t_minimap;

int				movements(t_data *data);
void			minimap(t_data *data, char *addr, int bpp, int line_len);
int				render(void *param);
unsigned int	rgb24(int fc[3]);
void			draw_line(t_raycast *raycast, t_data *data, t_raydata *rd);
void			check_side2(t_raydata *rd, t_raycast *raycast,
					t_data *data, t_direction **tex);
void			init_tex_and_draw(t_raycast *raycast,
					t_raydata *rd, t_direction *tex, t_data *d);
void			draw_wall(t_raydata *rd, t_data *data, t_direction *tex);
void			draw_floor_and_put_screen(t_raydata *rd,
					t_raycast *raycast, t_data *data);
void			all_checks(t_raycast *raycast, t_raydata *rd,
					t_data *data, t_direction *tex);
void			ray_check(t_raycast *raycast, t_raydata *rd, t_data *data);
void			ray_check2(t_raycast *raycast, t_raydata *rd, t_data *data);
void			ray_check3(t_raycast *raycast);
void			check_side(t_raydata *rd, t_raycast *raycast);
void			base_calc(t_raycast *raycast, t_data *data, t_raydata *rd);
void			base_calc2(t_raycast *raycast);

#endif