/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shoot.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravernhe <ravernhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 17:25:22 by ravernhe          #+#    #+#             */
/*   Updated: 2020/03/09 12:30:37 by ravernhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

void	texture_item(t_env *env, t_obb obb, int j)
{
	int	i;

	i = obb.first;
	while (i <= obb.last)
	{
		env->tri[i].index = env->nb_tex - j;
		i++;
	}
}

void	texture_portal(t_obb *obb, t_env *env)
{
	int	i;
	int	q;

	i = 0;
	while (obb[i].id != 6)
		i++;
	q = obb[i].first;
	while (q <= obb[i].last)
	{
		env->tri[q].index = env->nb_tex - 13;
		q++;
	}
}

void	id_hited(t_obb *obb, int i, t_env *env)
{
	if (obb[i].id == 5)
	{
		texture_item(env, obb[i], 12);
		obb[i].id = -1;
		env->end++;
		if (env->end == 6)
		{
			if (Mix_PlayChannel(-1, env->mix.portal, 0) == -1)
				ft_exit("music error");
		}
	}
	if (obb[i].id == 4)
	{
		vanish_item(env, obb[i]);
		obb[i].id = -3;
	}
	else if (obb[i].id == 3)
	{
		if (Mix_PlayChannel(-1, env->mix.damage, 0) == -1)
			ft_exit("music error");
	}
}

int		hit(t_vec3d tir, t_obb *obb, int borne, t_env *env)
{
	int		i;
	t_vec3d	max;
	t_vec3d	min;
	t_vec3d	trois;
	float	*data_vec;

	i = -1;
	if (!(data_vec = malloc(sizeof(float) * 6)))
		ft_exit("malloc error");
	init_vec(&trois, 3, 3, 3);
	while (++i <= borne)
	{
		init_col(data_vec, obb[i].center, vec_sub(obb[i].halfsize, trois));
		init_vec(&max, data_vec[0], data_vec[1], data_vec[2]);
		init_vec(&min, data_vec[3], data_vec[4], data_vec[5]);
		if (tir.x >= min.x && tir.y >= min.y && tir.z >= min.z &&\
			tir.x <= max.x && tir.y <= max.y && tir.z <= max.z)
		{
			id_hited(obb, i, env);
			free(data_vec);
			return (1);
		}
	}
	free(data_vec);
	return (0);
}

void	shoot(t_env *env)
{
	t_vec3d	tir;
	t_vec3d	dtir;

	tir.x = -(cos(env->fpitch) * sin(env->fyaw));
	tir.y = sin(-env->fpitch);
	tir.z = cos(env->fpitch) * cos(env->fyaw);
	tir.w = 0.0f;
	dtir = vec_add(tir, env->vcamera);
	while (hit(dtir, env->obb, env->nb_obb, env) == 0 &&\
		(fabs(dtir.x) < 400 || fabs(dtir.y) < 400 ||\
		fabs(dtir.z) < 400))
		dtir = vec_add(dtir, tir);
	if (env->end == 6)
	{
		texture_portal(env->obb, env);
		env->end++;
	}
}
