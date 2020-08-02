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

void	main_init(t_sdl *sdl, t_env *env)
{
	ft_init_sdl(sdl);
	ft_init_mix(&env->mix);
	init_vec(&env->vlookdir, 0.0f, 0.0f, 1.0f);
	init_vec(&env->vcamera, 0.0f, 0.0f, 0.0f);
	init_vec(&env->movement, 0.0f, 0.0f, 0.0f);
	init_vec(&env->spawn, 0.0f, 0.0f, 0.0f);
	env->tri = NULL;
	env->tour = NULL;
	env->tex = NULL;
	env->fyaw = 0.0f;
	env->fpitch = 0.0f;
	env->crunch = 0.0f;
	env->hp = 100;
	env->r_hp = 0;
	env->nrj = 0;
	env->shoot = 0;
	env->dy = 0;
	env->intro = 0;
	env->end = 0;
	env->fin = 0;
	env->noc = 0;
	env->matproj = mat_makeproj(90.0f, (float)SIZE_Y /\
	(float)SIZE_X, 0.1f, 1000.0f);
	sdl->x = 0;
	sdl->y = 0;
}

void	check_arg(char *av, int ac)
{
	int i;

	if (ac != 2)
		ft_exit("Usage : ./doom-nukem map_name.obj");
	i = ft_strlen(av);
	if (ft_strcmp(".obj", av + (i - 4)))
		ft_exit("Usage : ./doom-nukem map_name.obj");
}

int		main(int ac, char **av)
{
	t_sdl	sdl;
	t_env	env;
	t_vec3d	*list;
	t_vec2d	*uv;

	env.tuto = 0;
	main_init(&sdl, &env);
	list = NULL;
	uv = NULL;
	check_arg(av[1], ac);
	env = parse(av[1], env, list, uv);
	env.tex = xpm_parser(env.tex, env.nb_tex);
	save_tour(&env);
	display(&sdl, &env);
	Mix_PlayMusic(env.mix.music, -1);
	Mix_VolumeMusic(15);
	get_event(&sdl, &env);
	return (0);
}
