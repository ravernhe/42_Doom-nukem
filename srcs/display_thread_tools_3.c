/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_thread_tools_3.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravernhe <ravernhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 17:25:22 by ravernhe          #+#    #+#             */
/*   Updated: 2020/03/09 12:33:13 by ravernhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

t_tri	*tri_memcpy_n(t_tri *dest, t_tri *src, int start, int end)
{
	int	i;

	i = 0;
	while (start + i < end)
	{
		dest[i] = src[start + i];
		i++;
	}
	return (dest);
}

t_tri	*tri_mem_join(t_tri *dest, t_tri *src, int start, int end)
{
	int	i;

	i = 0;
	while (i < end)
	{
		dest[start + i] = src[i];
		i++;
	}
	free(src);
	return (dest);
}

t_tri	*end_a_clip(t_aclip *ac, int *end, t_tri *tmp_tri, t_tri *cpy_tri)
{
	*end += ac->k;
	tmp_tri = alloc_tri(tmp_tri, *end, cpy_tri);
	free(cpy_tri);
	ac->p++;
	return (tmp_tri);
}

t_tri	*init_loop(t_aclip *ac, int *end, t_tri *cpy_tri)
{
	ac->i = 0;
	ac->k = 0;
	if (!(cpy_tri = malloc(sizeof(t_tri) * (*end * 2))))
		ft_exit("malloc error");
	return (cpy_tri);
}

t_tri	*after_clip(t_tri *tri_proj, int start, int *end)
{
	t_tri	*cpy_tri;
	t_tri	*tmp_tri;
	t_tri	clipped[2];
	t_vec3d	plane[7];
	t_aclip	ac;

	init_plane(plane);
	ac.nc = 0;
	ac.p = 0;
	if (!(tmp_tri = malloc(sizeof(t_tri) * (*end - start))))
		ft_exit("malloc error");
	tmp_tri = tri_memcpy_n(tmp_tri, tri_proj, start, *end);
	*end -= start;
	while (ac.p < 4)
	{
		cpy_tri = init_loop(&ac, end, cpy_tri);
		while (ac.i < *end)
		{
			ac.nc = clip_all_plane(ac.p, plane, tmp_tri[ac.i], clipped);
			new_clip_tri(&ac, clipped, cpy_tri);
			ac.i++;
		}
		tmp_tri = end_a_clip(&ac, end, tmp_tri, cpy_tri);
	}
	return (tmp_tri);
}
