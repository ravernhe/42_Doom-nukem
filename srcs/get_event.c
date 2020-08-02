/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_event.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravernhe <ravernhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 17:25:22 by ravernhe          #+#    #+#             */
/*   Updated: 2020/03/09 12:30:37 by ravernhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

void	init_get_event(t_move *move, unsigned int *tick)
{
	init_move(move);
	tick[0] = 0;
	tick[1] = 0;
	tick[2] = 0;
	tick[3] = SDL_GetTicks();
	tick[4] = 0;
	tick[5] = SDL_GetTicks();
	tick[6] = 6;
}

void	process_keys1(t_gevent *g, unsigned int *tick, t_sdl *sdl, t_env *env)
{
	if (g->keys[SDL_SCANCODE_E] == 1 || SDL_GetTicks() - tick[3] > 17000)
		env->intro = 1;
	if ((g->keys[SDL_SCANCODE_P] == 1 &&\
		SDL_GetTicks() - tick[0] > 2000) || env->vcamera.y < -1500.0f)
	{
		env->vcamera = env->spawn;
		env->hp = 20;
		sdl->x = 0;
		sdl->y = 0;
		g->move.dy = 0.02f;
		tick[0] = SDL_GetTicks();
	}
	if (g->keys[SDL_SCANCODE_N] == 1 && SDL_GetTicks() - tick[6] > 250)
	{
		if (env->noc == 0)
			env->noc = 1;
		else
			env->noc = 0;
		tick[6] = SDL_GetTicks();
	}
	if (g->keys[SDL_SCANCODE_K] == 1 && SDL_GetTicks() - tick[1] > 250)
	{
		g->move.fly *= -1;
		tick[1] = SDL_GetTicks();
	}
}

void	process_keys2(t_gevent *g, unsigned int *tick, t_sdl *sdl, t_env *env)
{
	if (g->keys[SDL_SCANCODE_F] == 1 && env->r_hp == 1 && env->hp != 100)
	{
		env->r_hp = 0;
		env->hp = 100;
	}
	if ((env->nrj == 0 && SDL_GetTicks() - tick[2] > 1500))
	{
		env->nrj = 100;
		tick[2] = SDL_GetTicks();
	}
	get_move(&g->move, g->keys);
	mouse_cam(env, sdl);
	physic(env, &g->move, g->keys);
}

void	process_keys3(unsigned int *tick, t_env *env)
{
	if (SDL_GetMouseState(NULL, NULL) && SDL_BUTTON(SDL_BUTTON_LEFT))
	{
		if (env->nrj > 0 && SDL_GetTicks() - tick[2] > 600)
		{
			env->nrj -= 20;
			env->shoot = 1;
			if (Mix_PlayChannel(-1, env->mix.shoot, 0) == -1)
				ft_exit("music error");
			shoot(env);
			tick[2] = SDL_GetTicks();
			if (env->end == 7 && env->end++)
				tick[4] = tick[2];
			if (env->nrj == 0)
			{
				if (Mix_PlayChannel(-1, env->mix.reload, 0) == -1)
					ft_exit("music error");
			}
		}
	}
	if (env->end == 8)
		anim_port(env, tick[4]);
	if (SDL_GetTicks() - tick[2] > 200)
		env->shoot = 0;
	move_tourelle(env);
}

void	get_event(t_sdl *sdl, t_env *env)
{
	t_gevent		g;
	unsigned int	tick[7];

	init_get_event(&g.move, tick);
	while (SDL_PollEvent(&sdl->event) == 1 || SDL_PollEvent(&sdl->event) == 0)
	{
		g.keys = SDL_GetKeyboardState(NULL);
		if ((g.keys[SDL_SCANCODE_ESCAPE] == 1 || (sdl->event.type == SDL_QUIT)))
			clean_quit(sdl, env);
		if (env->fin == 0)
		{
			process_keys1(&g, tick, sdl, env);
			process_keys2(&g, tick, sdl, env);
			process_keys3(tick, env);
			if (SDL_GetTicks() - tick[5] > 3000)
			{
				shoot_tourelle(env);
				tick[5] = SDL_GetTicks();
			}
		}
		display(sdl, env);
	}
}
