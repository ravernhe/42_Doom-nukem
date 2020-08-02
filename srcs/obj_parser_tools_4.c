/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_parser_tools_4.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravernhe <ravernhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 17:25:22 by ravernhe          #+#    #+#             */
/*   Updated: 2020/03/09 12:09:55 by ravernhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

t_vec3d	*get_vec(t_pars *p, t_vec3d *list, char *buff)
{
	if (p->v[0] % 4096 == 0)
	{
		list = vec_add_size(list, p->m[0]);
		p->m[0]++;
	}
	list[p->v[0]] = p_vec(buff, list[p->v[0]]);
	p->v[0]++;
	return (list);
}

t_vec2d	*get_vec_tex(t_pars *p, t_vec2d *uv, char *buff)
{
	if (p->v[1] % 4096 == 0)
	{
		uv = vec2_add_size(uv, p->m[2]);
		p->m[2]++;
	}
	uv[p->v[1]] = p_vec2(buff, uv[p->v[1]]);
	p->v[1]++;
	return (uv);
}

void	get_face(t_env *env, t_pars *p, t_vec3d *list, t_vec2d *uv)
{
	if (env->nb_tri % 4096 == 0)
	{
		env->tri = tri_add_size(env->tri, p->m[1]);
		p->m[1]++;
	}
	env->tri[env->nb_tri] = p_tri(p->buff, env->tri[env->nb_tri], list, uv);
	env->tri[env->nb_tri].index = env->nb_tex - 1;
	env->nb_tri++;
}

void	get_obb(t_env *env, t_pars *p)
{
	if (env->nb_obb + 1 % 4096 == 0)
	{
		env->obb = obb_add_size(env->obb, p->o[0]);
		p->o[0]++;
	}
	env->obb[env->nb_obb + 1].id = 0;
	if (env->nb_obb != -1)
		env->obb[env->nb_obb] = p_obb(env->obb[env->nb_obb], env->tri +\
			p->o[1], env->nb_tri - 1 - p->o[1], p->o[1]);
	p->o[1] = env->nb_tri;
	env->nb_obb++;
}

t_env	end_pars(t_env *env, t_vec3d *list, t_vec2d *uv, t_pars *p)
{
	if (!(env->obb && env->tri && uv && list))
		ft_exit("Map error");
	env->obb[env->nb_obb] = p_obb(env->obb[env->nb_obb], env->tri +\
		p->o[1], env->nb_tri - 1 - p->o[1], p->o[1]);
	close(p->fd);
	free(uv);
	free(list);
	return (*env);
}
