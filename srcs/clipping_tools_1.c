/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clipping_tools_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravernhe <ravernhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 17:25:22 by ravernhe          #+#    #+#             */
/*   Updated: 2020/03/04 13:38:36 by ravernhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

void	clip_out_1(t_tri *clp, t_ctri tri, t_clip c)
{
	clp[0].p[0] = tri.in_p[0];
	clp[0].t[0] = tri.in_t[0];
	clp[0].t[1].u = c.t * (tri.out_t[0].u - tri.in_t[0].u) + tri.in_t[0].u;
	clp[0].t[1].v = c.t * (tri.out_t[0].v - tri.in_t[0].v) + tri.in_t[0].v;
	clp[0].t[1].w = c.t * (tri.out_t[0].w - tri.in_t[0].w) + tri.in_t[0].w;
}

void	clip_out_2(t_tri *clp, t_ctri tri, t_clip c, t_tri in_tri)
{
	clp[0].t[2].u = c.t * (tri.out_t[1].u - tri.in_t[0].u) + tri.in_t[0].u;
	clp[0].t[2].v = c.t * (tri.out_t[1].v - tri.in_t[0].v) + tri.in_t[0].v;
	clp[0].t[2].w = c.t * (tri.out_t[1].w - tri.in_t[0].w) + tri.in_t[0].w;
	clp[0].index = in_tri.index;
}

void	clip_in_1(t_tri *clp, t_ctri tri, t_clip c)
{
	clp[0].p[0] = tri.in_p[0];
	clp[0].p[1] = tri.in_p[1];
	clp[0].t[0] = tri.in_t[0];
	clp[0].t[1] = tri.in_t[1];
	clp[0].t[2].u = c.t * (tri.out_t[0].u - tri.in_t[0].u) + tri.in_t[0].u;
	clp[0].t[2].v = c.t * (tri.out_t[0].v - tri.in_t[0].v) + tri.in_t[0].v;
	clp[0].t[2].w = c.t * (tri.out_t[0].w - tri.in_t[0].w) + tri.in_t[0].w;
	clp[1].p[0] = tri.in_p[1];
	clp[1].t[0] = tri.in_t[1];
	clp[1].p[1] = clp[0].p[2];
	clp[1].t[1] = clp[0].t[2];
}

void	clip_in_2(t_tri *clp, t_ctri tri, t_clip c, t_tri in_tri)
{
	clp[1].t[2].u = c.t * (tri.out_t[0].u - tri.in_t[1].u) + tri.in_t[1].u;
	clp[1].t[2].v = c.t * (tri.out_t[0].v - tri.in_t[1].v) + tri.in_t[1].v;
	clp[1].t[2].w = c.t * (tri.out_t[0].w - tri.in_t[1].w) + tri.in_t[1].w;
	clp[0].index = in_tri.index;
	clp[1].index = in_tri.index;
}

int		clip_full_in_out(t_tri *clp, t_clip c, t_tri in_tri)
{
	if (c.in_pc == 0)
		return (0);
	if (c.in_pc == 3)
	{
		clp[0] = in_tri;
		return (1);
	}
	return (2);
}
