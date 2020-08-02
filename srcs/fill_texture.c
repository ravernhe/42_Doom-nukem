/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravernhe <ravernhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 17:25:22 by ravernhe          #+#    #+#             */
/*   Updated: 2020/02/10 17:04:09 by mamisdra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

void		fb(t_depth *depth, t_tex_var *var, t_texture tex, t_tri tri)
{
	while (++var->j <= var->bx && var->j <= SIZE_X)
	{
		while (((var->j > tri.p[0].x && var->j > tri.p[1].x && var->j >\
			tri.p[2].x) || (var->j < tri.p[0].x && var->j < tri.p[1].x &&\
			var->j < tri.p[2].x)) && (var->j <= var->bx && var->j <= SIZE_X))
			var->j++;
		if (var->j <= var->bx && var->j <= SIZE_X)
		{
			var->tex_u = (1.0f - var->t) * var->tex_su + var->t * var->tex_eu;
			var->tex_v = (1.0f - var->t) * var->tex_sv + var->t * var->tex_ev;
			var->tex_w = (1.0f - var->t) * var->tex_sw + var->t * var->tex_ew;
			if (var->tex_w > depth[var->i * SIZE_X + var->j].w)
			{
				var->tex_x = (int)(var->tex_u / var->tex_w * tex.x);
				var->tex_y = (int)(var->tex_v / var->tex_w * tex.y);
				var->tex_x = (var->tex_x < 0) ? 0 : var->tex_x;
				var->tex_y = (var->tex_y < 0) ? 0 : var->tex_y;
				var->tex_x = (var->tex_x >= tex.x) ? tex.x - 1 : var->tex_x;
				var->tex_y = (var->tex_y >= tex.y) ? tex.y - 1 : var->tex_y;
				if (tex.alphas[var->tex_y][var->tex_x] != 0)
					apply_texture(var, tex, depth);
			}
		}
		var->t += var->tstep;
	}
}

void		top_b(t_depth *depth, t_tex_var var, t_tri tri, t_texture tex)
{
	if (var.dy1 != 0)
	{
		var.i = tri.p[0].y;
		if (var.i < 0)
			var.i = -1;
		while (++var.i < tri.p[1].y && var.i < SIZE_Y)
		{
			var = further_step(var, tri, 0);
			var = ax_bx(var);
			fb(depth, &var, tex, tri);
		}
	}
	var = init_tex_var_second(tri, var);
	if (var.dy1 != 0)
	{
		var.i = tri.p[1].y - 1;
		if (var.i < 0)
			var.i = -1;
		while (++var.i < tri.p[2].y - 1 && var.i < SIZE_Y)
		{
			var = further_step(var, tri, 1);
			var = ax_bx(var);
			fb(depth, &var, tex, tri);
		}
	}
}

void		fill_texture(t_tri tri, t_texture tex, t_depth *depth, int noc)
{
	t_tex_var	var;

	var.noc = noc;
	tri = sort_point(tri);
	var = init_tex_var(tri, var);
	var = get_step(var);
	top_b(depth, var, tri, tex);
}
