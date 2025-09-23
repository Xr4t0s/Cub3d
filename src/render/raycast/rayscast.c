/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rayscast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nitadros <nitadros@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 00:17:11 by engiacom          #+#    #+#             */
/*   Updated: 2025/09/23 15:54:53 by nitadros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"
#include "raycast.h"
#include <math.h>

#define MAX_DIST 15.0

void	draw_line(char *addr, int x0, int y0, int x1, int y1, int color, int bpp, int line_len)
{
	// Algorithme de Bresenham pour tracer une ligne de (x0,y0) à (x1,y1)
	int dx = abs(x1 - x0);
	int dy = abs(y1 - y0);
	int sx;
	int sy;
	int err = dx - dy;

	// Direction du pas en X
	if (x0 < x1)
		sx = 1;
	else
		sx = -1;

	// Direction du pas en Y
	if (y0 < y1)
		sy = 1;
	else
		sy = -1;

	while (1)
	{
		// Évite d’écrire hors image (test minimal)
		if (x0 >= 0 && y0 >= 0)
		{
			char *pixel = addr + (y0 * line_len + x0 * (bpp / 8));
			*(unsigned int *)pixel = color;
		}
		// Point d’arrivée atteint
		if (x0 == x1 && y0 == y1)
			break;

		// Mise à jour d’erreur et déplacements
		int e2 = 2 * err;
		if (e2 > -dy)
		{
			err -= dy;
			x0 += sx;
		}
		if (e2 < dx)
		{
			err += dx;
			y0 += sy;
		}
	}
}

int	render(void *param)
{
	// Rendu principal : raycasting colonne par colonne + minimap
	t_data	*data = (t_data *)param;
	
	static void *img = NULL;
	static char *addr;
	static int bpp, line_len, endian;

	handle_keypress(0, data);
	
	// Création du buffer image une seule fois
	if (img == NULL)
	{
		img = mlx_new_image(data->mlx.mlx, data->mlx.width, data->mlx.height);
		addr = mlx_get_data_addr(img, &bpp, &line_len, &endian);
	}
	struct timeval tv;
    gettimeofday(&tv, NULL);
	long long start = (long long)tv.tv_sec * 1000 + tv.tv_usec / 1000;
	int x = 0;
	while (x < data->mlx.width)
	{
		t_raycast raycast;

		// Position du joueur (échelle : tes positions semblent en /10)
		raycast.posX = data->player.xP / data->scale;
		raycast.posY = data->player.yP / data->scale;

		// Direction de vue du joueur (angle en radians)
		raycast.dirX = cos(data->player.angle); // X=0,Y=-1 → Nord si angle = -pi/2
		raycast.dirY = sin(data->player.angle);

		// Plan caméra (contrôle le FOV)
		raycast.planeX = -raycast.dirY * tan(data->player.fov / 2);
		raycast.planeY =  raycast.dirX * tan(data->player.fov / 2);

		// Coordonnée caméra en X dans l’espace écran [-1, 1]
		raycast.cameraX = 2.0f * (float)x / (float)data->mlx.width - 1.0f;

		// Direction du rayon pour cette colonne écran
		raycast.rayDirX = raycast.dirX + raycast.planeX * raycast.cameraX;
		raycast.rayDirY = raycast.dirY + raycast.planeY * raycast.cameraX;

		// Case de la grille (carte) où commence le rayon
		raycast.mapX = (int)raycast.posX;
		raycast.mapY = (int)raycast.posY;

		// Distances à parcourir entre deux intersections de grille sur X/Y
		raycast.deltaDistX = fabs(1.0 / raycast.rayDirX);
		raycast.deltaDistY = fabs(1.0 / raycast.rayDirY);

		// Détermination du sens des pas sur X
		if (raycast.rayDirX < 0)
			raycast.stepX = -1;
		else
			raycast.stepX = 1;

		// Détermination du sens des pas sur Y
		if (raycast.rayDirY < 0)
			raycast.stepY = -1;
		else
			raycast.stepY = 1;

		// Distance du rayon jusqu’à la première arête verticale rencontrée
		if (raycast.rayDirX < 0)
			raycast.sideDistX = (raycast.posX - raycast.mapX) * raycast.deltaDistX;
		else
			raycast.sideDistX = (raycast.mapX + 1.0 - raycast.posX) * raycast.deltaDistX;

		// Distance du rayon jusqu’à la première arête horizontale rencontrée
		if (raycast.rayDirY < 0)
			raycast.sideDistY = (raycast.posY - raycast.mapY) * raycast.deltaDistY;
		else
			raycast.sideDistY = (raycast.mapY + 1.0 - raycast.posY) * raycast.deltaDistY;

		// DDA : on avance d’une case à la fois jusqu’au mur ou distance max
		int   hit = 0;
		float distance_travelled = 0.0f;

		while (hit == 0 && distance_travelled < MAX_DIST)
		{
			if (raycast.sideDistX < raycast.sideDistY)
			{
				distance_travelled = raycast.sideDistX;
				raycast.sideDistX += raycast.deltaDistX;
				raycast.mapX += raycast.stepX;
				raycast.side = 0; // impact sur une face verticale
			}
			else
			{
				distance_travelled = raycast.sideDistY;
				raycast.sideDistY += raycast.deltaDistY;
				raycast.mapY += raycast.stepY;
				raycast.side = 2; // impact sur une face horizontale
			}

			// Test de collision avec un mur ('1')
			if (data->map.map[raycast.mapY][raycast.mapX] == '1' || data->map.map[raycast.mapY][raycast.mapX] == 'D')
				hit = 1;
			if (data->map.map[raycast.mapY][raycast.mapX] == 'D' && data->raycast.door > 0 && (fabs(raycast.sideDistX) <= 2 || fabs(raycast.sideDistY) <= 2) && raycast.cameraX >= -0.30 && raycast.cameraX <= 0.30)
			{
				// printf("%f\n%f\n", raycast.sideDistX, raycast.sideDistY);
				data->map.map[raycast.mapY][raycast.mapX] = '*';
				data->raycast.door *= -1;
				hit = 0;
			}
			else if (data->map.map[raycast.mapY][raycast.mapX] == '*' && data->raycast.door > 0 && (fabs(raycast.sideDistX) <= 2 || fabs(raycast.sideDistY) <= 2) && raycast.cameraX >= -0.30 && raycast.cameraX <= 0.30)
			{
				// printf("%f\n%f\n", raycast.sideDistX, raycast.sideDistY);
				data->map.map[raycast.mapY][raycast.mapX] = 'D';
				data->raycast.door *= -1;
				hit = 1;
			}

			// Affine l’orientation de la face touchée (0→1 pour Est/Ouest, 2→3 pour Nord/Sud)
			if (raycast.side == 2)
			{
				if (raycast.posY > raycast.mapY)
					raycast.side = 3; // face sud
			}
			else
			{
				if (raycast.posX > raycast.mapX)
					raycast.side = 1; // face est
			}
		}
		
		double	hitX = raycast.posX + raycast.sideDistX * raycast.rayDirX;
		double	hitY = raycast.posY + raycast.sideDistY * raycast.rayDirY;

		

		// Distance perpendiculaire au mur (corrige l’effet fish-eye)
		float finalDist;
		if (hit)
		{
			if (raycast.side <= 1)
			{
				raycast.perpWallDist =
					(raycast.mapX - raycast.posX + (1 - raycast.stepX) / 2.0) / raycast.rayDirX;
			}
			else
			{
				raycast.perpWallDist =
					(raycast.mapY - raycast.posY + (1 - raycast.stepY) / 2.0) / raycast.rayDirY;
			}
			// Clamp par sécurité
			if (raycast.perpWallDist < MAX_DIST)
				finalDist = raycast.perpWallDist;
			else
				finalDist = MAX_DIST;
		}
		else
		{
			finalDist = MAX_DIST;
		}

		// Distance utilisée pour la hauteur de ligne (fallback si pas de hit)
		double dist;
		if (hit)
			dist = raycast.perpWallDist;
		else
			dist = 1e9;

		// Calcul de la hauteur de la “slice” de mur pour cette colonne
		int lineHeight;
		if (dist > 0.0)
			lineHeight = (int)(data->mlx.height / dist);
		else
			lineHeight = data->mlx.height;

		int drawStart  = (data->mlx.height - lineHeight) / 2;
		int drawEnd    = drawStart + lineHeight - 1;

		if (drawStart < 0)
			drawStart = 0;
		if (drawEnd >= data->mlx.height)
			drawEnd = data->mlx.height - 1;

		// Couleurs (ARGB 0x00RRGGBB ici, selon ton mlx)
		unsigned int ceil_col  = rgb24(data->map.textures.fc[0]); // plafond
		unsigned int floor_col = rgb24(data->map.textures.fc[1]); // sol

		// Couleur du mur selon la face frappée (ombrage simple)
		t_direction *tex = NULL;
		
		if (raycast.side == 1)
			tex = &data->map.textures.ea; // face est
		else if (raycast.side == 2)
			tex = &data->map.textures.no; // face nord
		else if (raycast.side == 3)
			tex = &data->map.textures.so; // face sud
		else
			tex = &data->map.textures.we; // face ouest

		// if (x == data->map.width / 2)
		// 	printf("%f %f\n", hitX, hitY);
		
		double wallX;
		if (raycast.side <= 1) // mur vertical (O/E)
			wallX = raycast.posY + dist * raycast.rayDirY;
		else                    // mur horizontal (N/S)
			wallX = raycast.posX + dist * raycast.rayDirX;

		wallX -= floor(wallX);
		
		int	texX = (int)(wallX * tex->width);
		// printf("wallx = %d\ntex->width = %d\n");
		double	step = (double)tex->height / (double)lineHeight;
		double	texPos = (drawStart - data->mlx.height /2.0 + lineHeight / 2.0) * step;
		// --- Remplissage plafond (y : 0 → drawStart-1)
		int y = 0;
		while (y < drawStart)
		{
			char *p = addr + (y * line_len + x * (bpp / 8));
			*(unsigned int *)p = ceil_col;
			y++;
		}

		// --- Colonne du mur (y : drawStart → drawEnd)
		y = drawStart;
		// if (x == data->mlx.width/2) {
		// 	fprintf(stderr,
		// 		"[tex] side=%d cell='%c' w=%d h=%d bpp=%d line=%d endian=%d addr=%p\n"
		// 		"      wallX=%.4f texX=%d dist=%.4f lineH=%d draw=[%d..%d] step=%.6f texPos0=%.6f\n",
		// 		raycast.side, data->map.map[raycast.mapY][raycast.mapX],
		// 		tex ? tex->width:0, tex ? tex->height:0, tex ? tex->bpp:0, tex ? tex->line_len:0,
		// 		tex ? tex->endian:0, tex ? tex->addr:NULL,
		// 		wallX, texX, dist, lineHeight, drawStart, drawEnd, step,
		// 		(drawStart - data->mlx.height / 2.0 + lineHeight / 2.0) * step
		// 	);
		// }

		while (y <= drawEnd)
		{
			unsigned int color;
			int texY = (int)texPos;
			
			if (texY < 0) texY = 0;
			if (texY >= tex->height) texY = tex->height - 1;
			texPos += step;

			char *src = tex->addr + texY * tex->line_len + texX * (tex->bpp/8);
    		color = *(unsigned int*)src;
			// printf("%u\n", color);
			
			char *p = addr + (y * line_len + x * (bpp / 8));
			*(unsigned int *)p = color;
			y++;
		}

		// --- Remplissage sol (y : drawEnd+1 → 719)
		y = drawEnd + 1;
		while (y < data->mlx.height)
		{
			char *p = addr + (y * line_len + x * (bpp / 8));
			*(unsigned int *)p = floor_col;
			y++;
		}

		// Point d’impact du rayon (utile pour la minimap / debug)
		hitX = raycast.posX + raycast.rayDirX * finalDist;
		hitY = raycast.posY + raycast.rayDirY * finalDist;

		// Trace le rayon sur la minimap (échelle *10)
		draw_line(
			addr,
			(int)(raycast.posX * data->scale + 1.5), (int)(raycast.posY * data->scale),
			(int)(hitX * data->scale),               (int)(hitY * data->scale),
			0x00FFFF00, bpp, line_len
		);

		x++;
	}
	data->raycast.door = -1;

	// Dessine la minimap par-dessus
	minimap(data->map.map, data, addr, bpp, line_len);

	// Affiche le buffer à l’écran
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.win, img, 0, 0);
	gettimeofday(&tv, NULL);
	long long end = (long long)tv.tv_sec * 1000 + tv.tv_usec / 1000;
	while (end - start <= 32)
	{
		usleep(100);
		gettimeofday(&tv, NULL);
		end = (long long)tv.tv_sec * 1000 + tv.tv_usec / 1000;
	}
	return (0);
}

