/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_tools_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravernhe <ravernhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 17:25:22 by ravernhe          #+#    #+#             */
/*   Updated: 2020/02/10 16:55:46 by mamisdra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

t_surf	fill_surf_struct(int x, int y, int i, int j)
{
	t_surf surf;

	surf.x = x;
	surf.y = y;
	surf.i = i;
	surf.j = j;
	return (surf);
}

void	fill_surface(SDL_Surface *surf, t_texture tex, int x, int y)
{
	int rgba[4];
	int	i;
	int	j;

	i = 0;
	while (i < y)
	{
		j = 0;
		while (j < x)
		{
			rgba[0] = tex.pixels[i][j] >> 16 & 255;
			rgba[1] = tex.pixels[i][j] >> 8 & 255;
			rgba[2] = tex.pixels[i][j] >> 0 & 255;
			rgba[3] = tex.alphas[i][j];
			((uint32_t*)surf->pixels)[j + i * x] =\
				SDL_MapRGBA(surf->format, rgba[0], rgba[1], rgba[2], rgba[3]);
			j++;
		}
		i++;
	}
}

void	surf_render(t_sdl *sdl, SDL_Surface *surface, t_surf s)
{
	SDL_Rect rect;

	rect.x = s.x;
	rect.y = s.y;
	rect.w = s.i;
	rect.h = s.j;
	sdl->texture = SDL_CreateTextureFromSurface(sdl->render, surface);
	SDL_FreeSurface(surface);
	SDL_RenderCopy(sdl->render, sdl->texture, NULL, &rect);
	SDL_DestroyTexture(sdl->texture);
}
