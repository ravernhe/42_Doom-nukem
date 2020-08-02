/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_tools_5.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravernhe <ravernhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 17:25:22 by ravernhe          #+#    #+#             */
/*   Updated: 2020/03/09 12:30:37 by ravernhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

void	calc_vol(t_vol *v, t_env *env, t_obb obb)
{
	if (env->tri[obb.first].p[0].x == env->tri[v->i].p[v->j].x &&\
			env->tri[obb.first].p[0].y == env->tri[v->i].p[v->j].y &&\
			env->tri[obb.first].p[0].z == env->tri[v->i].p[v->j].z &&\
			(v->tok[0] = 1))
		v->k++;
	else if (env->tri[obb.first].p[1].x == env->tri[v->i].p[v->j].x &&\
			env->tri[obb.first].p[1].y == env->tri[v->i].p[v->j].y &&\
			env->tri[obb.first].p[1].z == env->tri[v->i].p[v->j].z &&\
			(v->tok[1] = 1))
		v->k++;
	else if (env->tri[obb.first].p[2].x == env->tri[v->i].p[v->j].x &&\
			env->tri[obb.first].p[2].y == env->tri[v->i].p[v->j].y &&\
			env->tri[obb.first].p[2].z == env->tri[v->i].p[v->j].z &&\
			(v->tok[2] = 1))
		v->k++;
}

void	init_tok_vol(t_vol *v)
{
	v->j = -1;
	v->k = 0;
	v->tok[0] = 0;
	v->tok[1] = 0;
	v->tok[2] = 0;
}

void	init_check_slop(t_env *env, t_obb obb, float *volume, float *py)
{
	py[0] = 0.0f;
	py[1] = 0.0f;
	if (obb.last - obb.first < 10)
		*volume = cube_greg(env, obb);
	else
		*volume = cube_volume(env, obb);
}

int		return_slope(t_obb obb, float *py, float volume)
{
	if (obb.id == 9 && py[0] <= volume + volume * 105 / 100 &&\
		py[0] >= volume - volume * 105 / 100)
		return (1);
	if (obb.id == 8 && py[0] <= volume + volume * 1 / 100 &&\
		py[0] >= volume - volume * 1 / 100)
		return (1);
	if (py[0] <= volume + 10.0f && py[0] >= volume - 10.0f)
		return (1);
	return (0);
}

int		check_slope(t_env *env, t_vec3d cam, int flag, t_obb obb)
{
	int		i;
	float	volume;
	float	py[2];

	init_check_slop(env, obb, &volume, py);
	i = obb.first - 1;
	cam.y -= 2.9f;
	while (++i <= obb.last)
		py[0] += volume_pyr(env->tri[i], cam);
	if (flag == 0 && obb.id == 7)
	{
		i = obb.first - 1;
		cam.y -= 2.1f;
		while (++i <= obb.last)
			py[1] += volume_pyr(env->tri[i], cam);
		if (!(py[1] <= volume + 10.0f && py[1] >= volume - 10.0f) &&\
			(py[0] <= volume + 10.0f && py[0] >= volume - 10.0f))
			return (2);
	}
	return (return_slope(obb, py, volume));
}
