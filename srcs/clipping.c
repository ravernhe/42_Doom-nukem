/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clipping.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravernhe <ravernhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 17:25:22 by ravernhe          #+#    #+#             */
/*   Updated: 2020/03/04 13:38:36 by ravernhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

t_vec3d	vec_i_p(t_clip c, t_vec3d l_s, t_vec3d l_e, float *t)
{
	t_vec3d	line_s_t_e;
	t_vec3d	line_t_i;
	float	plane_d;
	float	ad;
	float	bd;

	c.p_n = vec_normalise(c.p_n);
	plane_d = -dot_product(c.p_n, c.p_p);
	ad = dot_product(l_s, c.p_n);
	bd = dot_product(l_e, c.p_n);
	*t = (-plane_d - ad) / (bd - ad);
	line_s_t_e = vec_sub(l_e, l_s);
	line_t_i = vec_mul(line_s_t_e, *t);
	return (vec_add(l_s, line_t_i));
}

float	dist(t_vec3d p, t_vec3d plane_n, t_vec3d plane_p)
{
	float	x;

	x = dot_product(plane_n, p) - dot_product(plane_n, plane_p);
	return (x);
}

void	get_point1(t_clip *c, t_ctri *tri, t_tri in_tri)
{
	if (c->d0 >= 0)
	{
		tri->in_p[c->in_pc++] = in_tri.p[0];
		tri->in_t[c->in_tc++] = in_tri.t[0];
	}
	else
	{
		tri->out_p[c->out_pc++] = in_tri.p[0];
		tri->out_t[c->out_tc++] = in_tri.t[0];
	}
	if (c->d1 >= 0)
	{
		tri->in_p[c->in_pc++] = in_tri.p[1];
		tri->in_t[c->in_tc++] = in_tri.t[1];
	}
	else
	{
		tri->out_p[c->out_pc++] = in_tri.p[1];
		tri->out_t[c->out_tc++] = in_tri.t[1];
	}
}

void	get_point2(t_clip *c, t_ctri *tri, t_tri in_tri)
{
	if (c->d2 >= 0)
	{
		tri->in_p[c->in_pc++] = in_tri.p[2];
		tri->in_t[c->in_tc++] = in_tri.t[2];
	}
	else
	{
		tri->out_p[c->out_pc++] = in_tri.p[2];
		tri->out_t[c->out_tc++] = in_tri.t[2];
	}
}

int		tri_clipping(t_vec3d p_p, t_vec3d p_n, t_tri in_tri, t_tri *clp)
{
	t_ctri	tri;
	t_clip	c;

	init_clip(&p_p, &p_n, &c, &in_tri);
	get_point1(&c, &tri, in_tri);
	get_point2(&c, &tri, in_tri);
	if (clip_full_in_out(clp, c, in_tri) != 2)
		return (clip_full_in_out(clp, c, in_tri));
	if (c.in_pc == 1 && c.out_pc == 2)
	{
		clp[0].p[1] = vec_i_p(c, tri.in_p[0], tri.out_p[0], &c.t);
		clip_out_1(clp, tri, c);
		clp[0].p[2] = vec_i_p(c, tri.in_p[0], tri.out_p[1], &c.t);
		clip_out_2(clp, tri, c, in_tri);
		return (1);
	}
	if (c.in_pc == 2 && c.out_pc == 1)
	{
		clp[0].p[2] = vec_i_p(c, tri.in_p[0], tri.out_p[0], &c.t);
		clip_in_1(clp, tri, c);
		clp[1].p[2] = vec_i_p(c, tri.in_p[1], tri.out_p[0], &c.t);
		clip_in_2(clp, tri, c, in_tri);
		return (2);
	}
	return (-1);
}
