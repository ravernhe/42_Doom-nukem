/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_tools_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravernhe <ravernhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 17:25:22 by ravernhe          #+#    #+#             */
/*   Updated: 2020/03/09 12:30:37 by ravernhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

float	cube_volume(t_env *env, t_obb obb)
{
	t_vol	v;

	v.i = obb.first;
	init_vol(&v, env, v.i);
	while (++v.i <= obb.last)
	{
		init_tok_vol(&v);
		while (++v.j < 3)
		{
			calc_vol(&v, env, obb);
			if (v.k == 2)
			{
				if (v.lon == 0.0f && v.tok[2] == 1)
					v.lon = get_third(v.lar, v.hau, env->tri[v.i]);
				else if (v.lar == 0.0f && v.tok[1] == 1)
					v.lar = get_third(v.lon, v.hau, env->tri[v.i]);
				else if (v.hau == 0.0f && v.tok[0] == 1)
					v.hau = get_third(v.lon, v.lar, env->tri[v.i]);
				break ;
			}
		}
	}
	return (v.lon * v.lar * v.hau);
}

void	collide_id(t_env *env, int i)
{
	if (env->obb[i].id == 1)
	{
		vanish_item(env, env->obb[i]);
		env->obb[i].id = -1;
		env->r_hp = 1;
	}
	else if (env->obb[i].id == 2)
	{
		env->vcamera = env->spawn;
		env->dy = 1;
		env->hp = 20;
		env->nrj = 100;
	}
	else if (env->obb[i].id == 6 && env->end >= 7)
		env->fin = 1;
}

int		verif_coll789(t_env *env, t_coll *c, t_vec3d cam, int flag)
{
	c->ret = check_slope(env, cam, flag, env->obb[c->i]);
	if (c->ret == 1)
	{
		free(c->d_vec);
		return (1);
	}
	else if (c->ret == 2)
	{
		env->vcamera.y += 1.5;
		free(c->d_vec);
		return (0);
	}
	return (2);
}

void	init_col_loop(t_coll *c, t_env *env, float flag)
{
	if (env->obb[c->i].id < 0)
		c->i++;
	init_col(c->d_vec, env->obb[c->i].center, env->obb[c->i].halfsize);
	init_vec(&c->max, c->d_vec[0], c->d_vec[1], c->d_vec[2]);
	init_vec(&c->min, c->d_vec[3], c->d_vec[4], c->d_vec[5]);
	if (flag == 3)
		c->min.y += 2;
}

int		collide(t_env *env, t_vec3d cam, int flag, float speed)
{
	t_coll	c;

	c.i = -1;
	init_collide(&c, flag, speed, &cam);
	while (++c.i <= env->nb_obb)
	{
		init_col_loop(&c, env, flag);
		if (cam.x >= c.min.x && cam.y >= c.min.y && cam.z >= c.min.z &&\
				cam.x <= c.max.x && cam.y <= c.max.y && cam.z <= c.max.z)
		{
			collide_id(env, c.i);
			if (env->obb[c.i].id != 7 && env->obb[c.i].id != 8 &&\
				env->obb[c.i].id != 9)
			{
				free(c.d_vec);
				return (1);
			}
			if (env->obb[c.i].id == 7 || env->obb[c.i].id == 8 ||\
				env->obb[c.i].id == 9)
				if ((c.ret2 = verif_coll789(env, &c, cam, flag)) != 2)
					return (c.ret2);
		}
	}
	free(c.d_vec);
	return (0);
}
