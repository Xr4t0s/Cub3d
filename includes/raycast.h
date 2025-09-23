/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nitadros <nitadros@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 23:56:10 by engiacom          #+#    #+#             */
/*   Updated: 2025/09/24 00:23:35 by nitadros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCAST_H
# define RAYCAST_H
# include "cube3d.h"

typedef	struct s_data t_data;

typedef struct s_raycast
{
	// Position du joueur
	double	posX;
	double	posY;

	// Direction du joueur
	double	dirX;
	double	dirY;

	// Plan de projection (champ de vision)
	double	planeX;
	double	planeY;

	// Coordonnée horizontale du rayon dans la caméra (de -1 à 1)
	double	cameraX;

	// Direction du rayon
	double	rayDirX;
	double	rayDirY;

	// Case actuelle dans la map (coordonnées entières)
	int		mapX;
	int		mapY;

	// Distance jusqu'au premier côté en X et Y
	double	sideDistX;
	double	sideDistY;

	// Distance entre deux lignes de grille (en X et en Y)
	double	deltaDistX;
	double	deltaDistY;

	// Distance perpendiculaire au mur (pour le fish-eye fix)
	double	perpWallDist;

	// Direction d’avancement du rayon dans la grille
	int		stepX;
	int		stepY;

	// Si un mur a été touché (flag DDA)
	int		hit;

	// Mur touché : 0 (vertical) ou 1 (horizontal)
	int		side;

	// Hauteur de la ligne à dessiner
	int		lineHeight;

	// Début et fin de la ligne à afficher (pixels à l’écran)
	int		drawStart;
	int		drawEnd;

	int		door;
}	t_raycast;

typedef	struct s_raydata
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		x;
	int		y;
	int		hit;
	float	distance_travelled;
	double		hitX;
	double		hitY;
	float		finalDist;
	double		dist;
	int			lineHeight;
	int 		drawStart;
	int 		drawEnd;
	unsigned int ceil_col;
	unsigned int floor_col;
	double wallX;
	int	texX;
	double	step;
	double	texPos;
}	t_raydata;


typedef	struct s_minimap
{
	void	*bg;
	void	*wall;
	void	*player;
	void	*bg4;
	
} t_minimap;

int				movements(t_data *data);
void			minimap(t_data *data, char *addr, int bpp, int line_len);
int				render(void *param);
unsigned int	rgb24(int fc[3]);

#endif