/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_tools_3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravernhe <ravernhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 17:25:22 by ravernhe          #+#    #+#             */
/*   Updated: 2020/03/09 12:30:37 by ravernhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

void	init_col(float *data_vec, t_vec3d cent, t_vec3d half)
{
	data_vec[0] = cent.x + half.x;
	data_vec[1] = cent.y + half.y;
	data_vec[2] = cent.z + half.z;
	data_vec[3] = cent.x - half.x;
	data_vec[4] = cent.y - half.y;
	data_vec[5] = cent.z - half.z;
}

void	vanish_item(t_env *env, t_obb obb)
{
	int	i;

	i = obb.first;
	while (i <= obb.last)
	{
		env->tri[i].index = env->nb_tex - 1;
		i++;
	}
}

float	ft_dist(t_vec3d a, t_vec3d b)
{
	float	value;

	value = sqrtf(pow((b.x - a.x), 2) + pow((b.y - a.y), 2) +\
		pow((b.z - a.z), 2));
	return (value);
}

float	cube_greg(t_env *env, t_obb obb)
{
	float	lon;
	float	lar;
	float	hau;
	float	tmp;
	int		i;

	i = obb.first;
	lon = ft_dist(env->tri[i].p[0], env->tri[i].p[1]);
	lar = ft_dist(env->tri[i].p[0], env->tri[i].p[2]);
	hau = ft_dist(env->tri[i].p[1], env->tri[i].p[2]);
	tmp = fmax(lon, fmax(lar, hau));
	if (lon == tmp)
		lon = 1.0f;
	else if (lar == tmp)
		lar = 1.0f;
	else if (hau == tmp)
		hau = 1.0f;
	return (lon * lar * hau);
}

float	volume_pyr(t_tri tri, t_vec3d cam)
{
	float	air_tri;
	float	s;
	float	d[3];
	float	h;
	t_vec3d	normal;

	init_vec(&normal, 0.0f, 0.0f, 0.0f);
	d[0] = ft_dist(tri.p[0], tri.p[1]);
	d[1] = ft_dist(tri.p[0], tri.p[2]);
	d[2] = ft_dist(tri.p[1], tri.p[2]);
	s = (d[0] + d[1] + d[2]) / 2;
	air_tri = sqrtf(s * (s - d[0]) * (s - d[1]) * (s - d[2]));
	normal = calc_normal(normal, tri);
	h = dot_product(normal, cam) - dot_product(normal, tri.p[1]);
	return (fabs(air_tri * h) / 3);
}
