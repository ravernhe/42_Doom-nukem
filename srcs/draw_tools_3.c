/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_tools_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravernhe <ravernhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 17:25:22 by ravernhe          #+#    #+#             */
/*   Updated: 2020/02/10 16:55:46 by mamisdra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

void	check_tex_size(t_env *env)
{
	if (env->tex[env->nb_tex - 3 - (env->hp / 20)].x != 156 ||\
			env->tex[env->nb_tex - 3 - (env->hp / 20)].y != 26)
		ft_exit("Texture error");
	if (env->tex[env->nb_tex - 3 - (env->nrj / 20)].x != 156 ||\
			env->tex[env->nb_tex - 3 - (env->nrj / 20)].y != 26)
		ft_exit("Texture error");
	if (env->tex[env->nb_tex - 2].x != 108 ||\
			env->tex[env->nb_tex - 2].y != 54)
		ft_exit("Texture error");
}

void	draw_weapon(t_sdl *sdl, t_env *env)
{
	t_mask		m;
	t_surf		s;
	SDL_Surface	*weapon;
	SDL_Surface	*laser;

	m.r = 0xff000000;
	m.g = 0x00ff0000;
	m.b = 0x0000ff00;
	m.a = 0x000000ff;
	weapon = SDL_CreateRGBSurface(0, 200, 166, 32, m.r, m.g, m.b, m.a);
	if (env->tex[env->nb_tex - 10].x != 200 ||\
			env->tex[env->nb_tex - 10].y != 166 ||\
			env->tex[env->nb_tex - 9].x != 98 ||\
			env->tex[env->nb_tex - 9].y != 169)
		ft_exit("Texture error");
	fill_surface(weapon, env->tex[env->nb_tex - 10], 200, 166);
	s = fill_surf_struct(468, 435, 200, 166);
	surf_render(sdl, weapon, s);
	if (env->shoot == 1)
	{
		laser = SDL_CreateRGBSurface(0, 98, 169, 32, m.r, m.g, m.b, m.a);
		fill_surface(laser, env->tex[env->nb_tex - 9], 98, 169);
		s = fill_surf_struct(400, 290, 98, 169);
		surf_render(sdl, laser, s);
	}
}
