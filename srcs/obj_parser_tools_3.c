/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_parser_tools_3.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravernhe <ravernhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 17:25:22 by ravernhe          #+#    #+#             */
/*   Updated: 2020/03/09 12:09:55 by ravernhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

void	get_spawn(t_env *env, char *str)
{
	int	i;

	i = 5;
	i = skip(str, i);
	env->vcamera.x = ft_atof(str + i);
	i = skip(str, i);
	env->vcamera.y = ft_atof(str + i);
	i = skip(str, i);
	env->vcamera.z = ft_atof(str + i);
	env->spawn = env->vcamera;
}

t_obb	*obb_memcpy(t_obb *dest, t_obb *src, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		dest[i] = src[i];
		i++;
	}
	return (dest);
}

t_obb	*obb_add_size(t_obb *data, int size)
{
	t_obb	*cpy;

	if (!(cpy = malloc(sizeof(t_obb) * (4096 * size))))
		ft_exit("malloc error");
	if (size > 1)
		cpy = obb_memcpy(cpy, data, 4096 * (size - 1));
	free(data);
	return (cpy);
}

t_obb	apply_id(t_obb obb, t_vec3d min, t_vec3d max)
{
	obb.halfsize.x = (max.x - min.x) / 2;
	obb.halfsize.y = (max.y - min.y) / 2;
	obb.halfsize.z = (max.z - min.z) / 2;
	obb.halfsize.w = 1.0f;
	obb.center.x = min.x + obb.halfsize.x;
	obb.center.y = min.y + obb.halfsize.y;
	obb.center.z = min.z + obb.halfsize.z;
	obb.center.w = 1.0f;
	if (obb.id == 3)
	{
		obb.halfsize.x -= 1.7;
		obb.halfsize.y -= 1.7;
		obb.halfsize.z -= 1.7;
	}
	obb.halfsize.x += 3;
	obb.halfsize.y += 3;
	obb.halfsize.z += 3;
	if (obb.id == 6)
	{
		obb.halfsize.x += 2;
		obb.halfsize.y += 2;
		obb.halfsize.z += 2;
	}
	return (obb);
}

t_obb	p_obb(t_obb obb, t_tri *tri, int nb, int first)
{
	int		i;
	int		j;
	t_vec3d	min;
	t_vec3d	max;

	i = -1;
	init_vec(&min, tri[0].p[0].x, tri[0].p[0].y, tri[0].p[0].z);
	init_vec(&max, tri[0].p[0].x, tri[0].p[0].y, tri[0].p[0].z);
	while (++i < nb)
	{
		j = -1;
		while (++j < 3)
		{
			min.x = (tri[i].p[j].x < min.x) ? tri[i].p[j].x : min.x;
			min.y = (tri[i].p[j].y < min.y) ? tri[i].p[j].y : min.y;
			min.z = (tri[i].p[j].z < min.z) ? tri[i].p[j].z : min.z;
			max.x = (tri[i].p[j].x > max.x) ? tri[i].p[j].x : max.x;
			max.y = (tri[i].p[j].y > max.y) ? tri[i].p[j].y : max.y;
			max.z = (tri[i].p[j].z > max.z) ? tri[i].p[j].z : max.z;
		}
	}
	obb = apply_id(obb, min, max);
	obb.last = nb + first;
	obb.first = obb.last - nb;
	return (obb);
}
