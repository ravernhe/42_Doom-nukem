/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_tools_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravernhe <ravernhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 17:25:22 by ravernhe          #+#    #+#             */
/*   Updated: 2020/03/09 12:33:13 by ravernhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

void	put_colors(t_depth *depth, t_sdl *sdl, int x, int y)
{
	float	r;
	float	g;
	float	b;

	if (depth[y * SIZE_X + x].w != 0.0f)
	{
		r = depth[y * SIZE_X + x].color >> 16 & 255;
		g = depth[y * SIZE_X + x].color >> 8 & 255;
		b = depth[y * SIZE_X + x].color >> 0 & 255;
		((uint32_t*)sdl->surface->pixels)[x + y * SIZE_X] =\
			SDL_MapRGBA(sdl->surface->format, r, g, b, 255);
	}
	else
		((uint32_t*)sdl->surface->pixels)[x + y * SIZE_X] =\
			SDL_MapRGBA(sdl->surface->format, 0, 0, 0, 0);
}

void	display_surface(t_depth *depth, t_sdl *sdl)
{
	int		x;
	int		y;

	y = 0;
	while (y < SIZE_Y)
	{
		x = 0;
		while (x < SIZE_X)
		{
			put_colors(depth, sdl, x, y);
			x++;
		}
		y++;
	}
	sdl->texture = SDL_CreateTextureFromSurface(sdl->render, sdl->surface);
	SDL_FreeSurface(sdl->surface);
	SDL_RenderCopy(sdl->render, sdl->texture, NULL, NULL);
	SDL_DestroyTexture(sdl->texture);
}

void	init_and_fill(int d, t_env *env, t_depth *depth, t_tri *n_tri)
{
	int	i;

	i = 0;
	while (i < SIZE_X * SIZE_Y)
	{
		depth[i].w = 0.0f;
		depth[i].color = 0;
		i++;
	}
	i = 0;
	while (i < d)
	{
		fill_texture(n_tri[i], env->tex[n_tri[i].index], depth, env->noc);
		i++;
	}
}

void	tri_to_pixel(t_sdl *sdl, t_tri *tri_proj, int d, t_env *env)
{
	t_tri	*n_tri;
	int		nb_thread;
	t_depth	*depth;
	t_mask	m;

	m.r = 0xff000000;
	m.g = 0x00ff0000;
	m.b = 0x0000ff00;
	m.a = 0x000000ff;
	SDL_SetRenderDrawColor(sdl->render, 54, 204, 209, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(sdl->render);
	nb_thread = (d < NB_THREAD) ? d : NB_THREAD;
	n_tri = do_thread(tri_proj, &d, nb_thread);
	if (!(depth = malloc(sizeof(t_depth) * (SIZE_X * SIZE_Y))))
		ft_exit("malloc error");
	init_and_fill(d, env, depth, n_tri);
	sdl->surface = SDL_CreateRGBSurface(0, 800, 600, 32, m.r, m.g, m.b, m.a);
	display_surface(depth, sdl);
	free(depth);
	free(n_tri);
}
