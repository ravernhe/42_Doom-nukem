/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravernhe <ravernhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 17:25:22 by ravernhe          #+#    #+#             */
/*   Updated: 2020/03/09 12:30:37 by ravernhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

void	hit_id_4(t_obb *obb, float *data_vec, t_hit *h, int i)
{
	obb[i].halfsize.x -= 3;
	obb[i].halfsize.y -= 3;
	obb[i].halfsize.z -= 3;
	init_col(data_vec, obb[i].center, obb[i].halfsize);
	obb[i].halfsize.x += 3;
	obb[i].halfsize.y += 3;
	obb[i].halfsize.z += 3;
	init_vec(&h->max, data_vec[0], data_vec[1], data_vec[2]);
	init_vec(&h->min, data_vec[3], data_vec[4], data_vec[5]);
}

int		free_datavec(float *data_vec)
{
	free(data_vec);
	return (1);
}

void	init_hit_player(float **data_vec, int *i, t_env *env, t_hit *h)
{
	if (!(*data_vec = malloc(sizeof(float) * 6)))
		ft_exit("malloc error");
	*i = 0;
	init_vec(&h->pmax, env->vcamera.x + 1, env->vcamera.y + 1,\
		env->vcamera.z + 1);
	init_vec(&h->pmin, env->vcamera.x - 1, env->vcamera.y - 1,\
		env->vcamera.z - 1);
}

int		hit_player(t_vec3d tir, t_obb *obb, int borne, t_env *env)
{
	int		i;
	float	*data_vec;
	t_hit	h;

	init_hit_player(&data_vec, &i, env, &h);
	while (i <= borne)
	{
		if (obb[i].id != 4)
		{
			hit_id_4(obb, data_vec, &h, i);
			if (tir.x >= h.pmin.x && tir.y >= h.pmin.y && tir.z >= h.pmin.z &&\
					tir.x <= h.pmax.x && tir.y <= h.pmax.y && tir.z <= h.pmax.z)
			{
				free(data_vec);
				return (2);
			}
			else if (tir.x >= h.min.x && tir.y >= h.min.y && tir.z >= h.min.z\
				&& tir.x <= h.max.x && tir.y <= h.max.y && tir.z <= h.max.z)
				return (free_datavec(data_vec));
		}
		i++;
	}
	free(data_vec);
	return (0);
}
