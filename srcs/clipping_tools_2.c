/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clipping_tools_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravernhe <ravernhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 17:25:22 by ravernhe          #+#    #+#             */
/*   Updated: 2020/03/04 13:38:36 by ravernhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

void	init_clip(t_vec3d *p_p, t_vec3d *p_n, t_clip *c, t_tri *in_tri)
{
	*p_n = vec_normalise(*p_n);
	c->t = 0;
	c->out_pc = 0;
	c->in_pc = 0;
	c->out_tc = 0;
	c->in_tc = 0;
	c->d0 = dist(in_tri->p[0], *p_n, *p_p);
	c->d1 = dist(in_tri->p[1], *p_n, *p_p);
	c->d2 = dist(in_tri->p[2], *p_n, *p_p);
	c->p_p = *p_p;
	c->p_n = *p_n;
}
