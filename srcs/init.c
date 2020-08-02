/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravernhe <ravernhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 17:25:22 by ravernhe          #+#    #+#             */
/*   Updated: 2020/03/09 12:30:37 by ravernhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

void	ft_init_sdl(t_sdl *sdl)
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_AUDIO) < 0)
		ft_exit("SDL_Init error");
	if (!(sdl->window = SDL_CreateWindow("DOOM_TEST",
					SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,\
					SIZE_X, SIZE_Y, 0)))
		ft_exit("SDL_CreateWindow error");
	if (!(sdl->render = SDL_CreateRenderer(sdl->window, -1,\
		SDL_RENDERER_PRESENTVSYNC)))
		ft_exit("SDL_CreateRenderer error");
	SDL_SetRelativeMouseMode(SDL_TRUE);
}

void	ft_init_mix(t_mix *mix)
{
	int	i;

	i = -1;
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 512) == -1)
		ft_exit("load sound error");
	if (!(mix->shoot = Mix_LoadWAV("sound/shoot.wav")))
		ft_exit("load sound error");
	if (!(mix->damage = Mix_LoadWAV("sound/damage.wav")))
		ft_exit("load sound error");
	if (!(mix->reload = Mix_LoadWAV("sound/reload.wav")))
		ft_exit("load sound error");
	if (!(mix->jump = Mix_LoadWAV("sound/jump.wav")))
		ft_exit("load sound error");
	if (!(mix->portal = Mix_LoadWAV("sound/portal.wav")))
		ft_exit("load sound error");
	if (!(mix->music = Mix_LoadMUS("sound/music.wav")))
		ft_exit("load sound error");
	Mix_AllocateChannels(16);
	while (++i < 16)
		Mix_Volume(i, MIX_MAX_VOLUME / 2);
}

void	init_vec(t_vec3d *v, float x, float y, float z)
{
	v->x = x;
	v->y = y;
	v->z = z;
	v->w = 1.0f;
}
