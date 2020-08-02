/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tourelle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravernhe <ravernhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 17:25:22 by ravernhe          #+#    #+#             */
/*   Updated: 2020/03/09 12:30:37 by ravernhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

void	face_tourelle(t_env *env, t_obb obb, t_tri *tour)
{
	float		x;
	float		z;
	float		angle;
	int			k[2];
	t_mat4x4	mat;

	x = env->vcamera.x - obb.center.x;
	z = env->vcamera.z - obb.center.z;
	angle = atan2f(z, x) * 180 / M_PI;
	if (angle < 0)
		angle += 360;
	angle *= M_PI / 180.0f;
	mat = init_matroty(angle);
	k[0] = -1;
	while (++k[0] < obb.last - obb.first)
	{
		k[1] = -1;
		while (++k[1] < 3)
		{
			env->tri[k[0] + obb.first].p[k[1]] =\
			mat_mulvec(mat, vec_sub(tour[k[0]].p[k[1]], obb.center));
			env->tri[k[0] + obb.first].p[k[1]] =\
			vec_add(env->tri[k[0] + obb.first].p[k[1]], obb.center);
		}
	}
}

void	move_tourelle(t_env *env)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (i <= env->nb_obb)
	{
		if (env->obb[i].id == 4)
		{
			face_tourelle(env, env->obb[i], env->tour[j]);
			j++;
		}
		if (env->obb[i].id == -3)
			j++;
		i++;
	}
}

void	dead_by_turret(t_env *env)
{
	env->vcamera = env->spawn;
	env->dy = 1;
	env->hp = 100;
	env->nrj = 100;
}

void	piou_tourelle(t_env *env, t_obb obb)
{
	float	x;
	float	z;
	float	angle;
	t_vec3d	tir;
	t_vec3d	dtir;

	x = env->vcamera.x - obb.center.x;
	z = env->vcamera.z - obb.center.z;
	angle = atan2f(z, x) * 180 / M_PI;
	if (angle < 0)
		angle += 360;
	angle *= M_PI / 180.0f;
	init_vec(&tir, cos(angle), 0.0f, sin(angle));
	dtir = vec_add(tir, obb.center);
	while (hit_player(dtir, env->obb, env->nb_obb, env) == 0)
		dtir = vec_add(dtir, tir);
	if (hit_player(dtir, env->obb, env->nb_obb, env) == 2)
	{
		env->hp -= 20.0f;
		if (Mix_PlayChannel(-1, env->mix.damage, 0) == -1)
			ft_exit("music error");
		if (env->hp == 0)
			dead_by_turret(env);
	}
}

void	shoot_tourelle(t_env *env)
{
	int	i;

	i = 0;
	while (i <= env->nb_obb)
	{
		if (env->obb[i].id == 4)
			piou_tourelle(env, env->obb[i]);
		i++;
	}
}
