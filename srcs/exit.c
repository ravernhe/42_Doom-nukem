/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravernhe <ravernhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 17:25:22 by ravernhe          #+#    #+#             */
/*   Updated: 2020/03/09 12:30:37 by ravernhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

void	ft_exit(char *message)
{
	ft_putstr(message);
	ft_putchar('\n');
	exit(0);
}

void	clean_quit_audio(t_env *env)
{
	Mix_FreeMusic(env->mix.music);
	Mix_FreeChunk(env->mix.shoot);
	Mix_FreeChunk(env->mix.damage);
	Mix_FreeChunk(env->mix.reload);
	Mix_FreeChunk(env->mix.jump);
	Mix_FreeChunk(env->mix.portal);
	Mix_CloseAudio();
}

void	clean_quit(t_sdl *sdl, t_env *env)
{
	int	i;
	int	n;

	n = -1;
	while (++n < env->nb_tex)
	{
		i = -1;
		while (++i < env->tex[n].y)
		{
			free(env->tex[n].pixels[i]);
			free(env->tex[n].alphas[i]);
		}
		free(env->tex[n].name);
		free(env->tex[n].pixels);
		free(env->tex[n].alphas);
	}
	free(env->tex);
	free(env->tri);
	free(env->obb);
	clean_quit_audio(env);
	SDL_DestroyRenderer(sdl->render);
	SDL_DestroyWindow(sdl->window);
	SDL_Quit();
	exit(0);
}
