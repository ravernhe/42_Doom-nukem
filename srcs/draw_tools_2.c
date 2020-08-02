/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_tools_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravernhe <ravernhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 17:25:22 by ravernhe          #+#    #+#             */
/*   Updated: 2020/02/10 16:55:46 by mamisdra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

void	draw_hud(t_sdl *sdl, t_env *env)
{
	t_mask		m;
	t_surf		s;
	SDL_Surface	*j_hp;
	SDL_Surface	*j_nrj;
	SDL_Surface	*j;

	m.r = 0xff000000;
	m.g = 0x00ff0000;
	m.b = 0x0000ff00;
	m.a = 0x000000ff;
	j_hp = SDL_CreateRGBSurface(0, 156, 26, 32, m.r, m.g, m.b, m.a);
	j_nrj = SDL_CreateRGBSurface(0, 156, 26, 32, m.r, m.g, m.b, m.a);
	j = SDL_CreateRGBSurface(0, 108, 54, 32, m.r, m.g, m.b, m.a);
	check_tex_size(env);
	fill_surface(j_hp, env->tex[env->nb_tex - 3 - (env->hp / 20)], 156, 26);
	fill_surface(j_nrj, env->tex[env->nb_tex - 3 - (env->nrj / 20)], 156, 26);
	fill_surface(j, env->tex[env->nb_tex - 2], 108, 54);
	s = fill_surf_struct(108, 525, 156, 26);
	surf_render(sdl, j_nrj, s);
	s = fill_surf_struct(108, 556, 156, 26);
	surf_render(sdl, j_hp, s);
	s = fill_surf_struct(0, 525, 108, 54);
	surf_render(sdl, j, s);
}

void	draw_intro(t_sdl *sdl, t_env *env)
{
	t_mask		m;
	t_surf		s;
	SDL_Surface	*border;

	m.r = 0xff000000;
	m.g = 0x00ff0000;
	m.b = 0x0000ff00;
	m.a = 0x000000ff;
	border = SDL_CreateRGBSurface(0, 800, 150, 32, m.r, m.g, m.b, m.a);
	if (env->tex[env->nb_tex - 11].x != 800 ||\
			env->tex[env->nb_tex - 11].y != 150)
		ft_exit("Texture error");
	fill_surface(border, env->tex[env->nb_tex - 11], 800, 150);
	s = fill_surf_struct(0, 450, 800, 150);
	surf_render(sdl, border, s);
}

void	draw_r_hp(t_sdl *sdl, t_env *env, int i)
{
	t_mask		m;
	t_surf		s;
	SDL_Surface	*orbe;

	m.r = 0xff000000;
	m.g = 0x00ff0000;
	m.b = 0x0000ff00;
	m.a = 0x000000ff;
	orbe = SDL_CreateRGBSurface(0, 21, 21, 32, m.r, m.g, m.b, m.a);
	if (env->tex[env->nb_tex - 16 - i].x != 21 ||\
			env->tex[env->nb_tex - 16 - i].y != 21)
		ft_exit("Texture error");
	fill_surface(orbe, env->tex[env->nb_tex - 16 - i], 21, 21);
	s = fill_surf_struct(270, 560, 21, 21);
	surf_render(sdl, orbe, s);
}

void	draw_fin(t_sdl *sdl, t_env *env)
{
	t_mask		m;
	t_surf		s;
	SDL_Surface	*border;

	m.r = 0xff000000;
	m.g = 0x00ff0000;
	m.b = 0x0000ff00;
	m.a = 0x000000ff;
	border = SDL_CreateRGBSurface(0, 800, 600, 32, m.r, m.g, m.b, m.a);
	if (env->tex[env->nb_tex - 18].x != 800 ||\
			env->tex[env->nb_tex - 18].y != 600)
		ft_exit("Texture error");
	fill_surface(border, env->tex[env->nb_tex - 18], 800, 600);
	s = fill_surf_struct(0, 0, 800, 600);
	surf_render(sdl, border, s);
}

void	draw_stuff(t_sdl *sdl, t_env *env)
{
	if (env->intro == 0 && env->tuto == 1)
		draw_intro(sdl, env);
	else
	{
		if (env->r_hp == 0)
			draw_r_hp(sdl, env, 0);
		else
			draw_r_hp(sdl, env, 1);
		draw_weapon(sdl, env);
		draw_hud(sdl, env);
	}
	draw_crosshair(sdl);
	if (env->fin == 1)
		draw_fin(sdl, env);
}
