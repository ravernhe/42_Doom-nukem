/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_tools_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravernhe <ravernhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 17:25:22 by ravernhe          #+#    #+#             */
/*   Updated: 2020/03/08 19:05:45 by ravernhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

void	init_plane(t_vec3d *plane)
{
	init_vec(&plane[0], 0.0f, 0.0f, 0.0f);
	init_vec(&plane[1], 1.0f, 0.0f, 0.0f);
	init_vec(&plane[2], -1.0f, 0.0f, 0.0f);
	init_vec(&plane[3], 0.0f, 1.0f, 0.0f);
	init_vec(&plane[4], 0.0f, -1.0f, 0.0f);
	init_vec(&plane[5], (float)SIZE_X - 1, 0.0f, 0.0f);
	init_vec(&plane[6], 0.0f, (float)SIZE_Y - 1, 0.0f);
}

int		clip_all_plane(int k, t_vec3d *p, t_tri tmp, t_tri *cl)
{
	int			nclipped;
	static int	q;

	if (!q)
		q = 0;
	nclipped = 0;
	if (k == 0)
		nclipped = tri_clipping(p[0], p[3], tmp, cl);
	else if (k == 1)
		nclipped = tri_clipping(p[5], p[2], tmp, cl);
	else if (k == 2)
		nclipped = tri_clipping(p[0], p[1], tmp, cl);
	else if (k == 3)
		nclipped = tri_clipping(p[6], p[4], tmp, cl);
	return (nclipped);
}

void	new_clip_tri(t_aclip *ac, t_tri *c, t_tri *cpy)
{
	int	n;

	n = 0;
	while (n < ac->nc)
	{
		cpy[ac->i + n + ac->k] = c[n];
		n++;
	}
	if (ac->nc == 2)
		ac->k += 1;
	if (ac->nc == 0)
		ac->k -= 1;
}

t_tri	*alloc_tri(t_tri *tmp_tri, int d, t_tri *cpy_tri)
{
	free(tmp_tri);
	if (!(tmp_tri = malloc(sizeof(t_tri) * (d))))
		ft_exit("malloc error");
	tmp_tri = tri_memcpy(tmp_tri, cpy_tri, (size_t)d);
	return (tmp_tri);
}
