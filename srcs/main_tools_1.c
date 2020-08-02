/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravernhe <ravernhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 17:25:22 by ravernhe          #+#    #+#             */
/*   Updated: 2020/03/09 12:30:37 by ravernhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

void	mouse_cam(t_env *env, t_sdl *sdl)
{
	float	rad;
	int		x;
	int		y;
	int		reset;

	SDL_GetRelativeMouseState(&x, &y);
	reset = (int)(360.0f / MSPEED);
	rad = M_PI / 180.0f;
	sdl->x += x;
	if (sdl->x > reset)
		sdl->x -= reset;
	else if (sdl->x < -reset)
		sdl->x += reset;
	env->fyaw = sdl->x * MSPEED * rad;
	if ((sdl->y + y) * MSPEED * rad < 90.0f * rad && (sdl->y + y) *\
		MSPEED * rad > -90.0f * rad)
	{
		sdl->y += y;
		env->fpitch = sdl->y * MSPEED * rad;
	}
}

void	init_save_tour(int *i, t_env *env, int *tour)
{
	*i = 0;
	*tour = 0;
	while (*i <= env->nb_obb)
	{
		if (env->obb[*i].id == 4)
			*tour += 1;
		*i += 1;
	}
	if (!(env->tour = malloc(sizeof(t_tri *) * *tour)))
		ft_exit("malloc error");
	*i = -1;
}

void	save_tour(t_env *env)
{
	int	i;
	int	j;
	int	k;
	int	tour;

	init_save_tour(&i, env, &tour);
	while (++i < tour)
	{
		if (!(env->tour[i] = malloc(sizeof(t_tri) * 12)))
			ft_exit("malloc error");
	}
	i = -1;
	k = 0;
	while (++i <= env->nb_obb)
	{
		if (env->obb[i].id == 4)
		{
			j = env->obb[i].first - 1;
			while (++j <= env->obb[i].last)
				env->tour[k][j - env->obb[i].first] = env->tri[j];
			k++;
		}
	}
}

void	anim_port(t_env *env, unsigned int tick)
{
	unsigned int	tick1;

	tick1 = SDL_GetTicks();
	if ((tick1 % 2) == 0)
		texture_portal(env->obb, env);
	else
		texture_portal2(env->obb, env);
	if (tick1 - tick > 1500)
	{
		texture_portal(env->obb, env);
		env->end++;
	}
}
