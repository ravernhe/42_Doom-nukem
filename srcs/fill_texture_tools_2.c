/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_texture_tools_1.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravernhe <ravernhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 17:25:22 by ravernhe          #+#    #+#             */
/*   Updated: 2020/02/10 17:04:09 by mamisdra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

t_tex_var	ax_bx(t_tex_var var)
{
	if (var.ax > var.bx)
	{
		swap_i(&var.ax, &var.bx);
		swap_f(&var.tex_su, &var.tex_eu);
		swap_f(&var.tex_sv, &var.tex_ev);
		swap_f(&var.tex_sw, &var.tex_ew);
	}
	var.tex_u = var.tex_su;
	var.tex_v = var.tex_sv;
	var.tex_w = var.tex_sw;
	if (var.bx - var.ax != 0)
		var.tstep = 1.0f / ((float)(var.bx - var.ax));
	var.t = 0.0f;
	var.j = var.ax - 1;
	if (var.j < 0)
		var.j = -1;
	return (var);
}

t_tex_var	further_step(t_tex_var var, t_tri tri, int tok)
{
	if (tok == 0)
	{
		var.ax = (int)(tri.p[0].x + (float)(var.i - tri.p[0].y) * var.dax_step);
		var.bx = (int)(tri.p[0].x + (float)(var.i - tri.p[0].y) * var.dbx_step);
		var.tex_su = tri.t[0].u + (float)(var.i - tri.p[0].y) * var.du1_step;
		var.tex_sv = tri.t[0].v + (float)(var.i - tri.p[0].y) * var.dv1_step;
		var.tex_sw = tri.t[0].w + (float)(var.i - tri.p[0].y) * var.dw1_step;
		var.tex_eu = tri.t[0].u + (float)(var.i - tri.p[0].y) * var.du2_step;
		var.tex_ev = tri.t[0].v + (float)(var.i - tri.p[0].y) * var.dv2_step;
		var.tex_ew = tri.t[0].w + (float)(var.i - tri.p[0].y) * var.dw2_step;
	}
	else
	{
		var.ax = (int)(tri.p[1].x + (float)(var.i - tri.p[1].y) * var.dax_step);
		var.bx = (int)(tri.p[0].x + (float)(var.i - tri.p[0].y) * var.dbx_step);
		var.tex_su = tri.t[1].u + (float)(var.i - tri.p[1].y) * var.du1_step;
		var.tex_sv = tri.t[1].v + (float)(var.i - tri.p[1].y) * var.dv1_step;
		var.tex_sw = tri.t[1].w + (float)(var.i - tri.p[1].y) * var.dw1_step;
		var.tex_eu = tri.t[0].u + (float)(var.i - tri.p[0].y) * var.du2_step;
		var.tex_ev = tri.t[0].v + (float)(var.i - tri.p[0].y) * var.dv2_step;
		var.tex_ew = tri.t[0].w + (float)(var.i - tri.p[0].y) * var.dw2_step;
	}
	return (var);
}

t_tri		sort_point(t_tri tri)
{
	if (tri.p[1].y < tri.p[0].y)
	{
		swap_v(&tri.p[0], &tri.p[1]);
		swap_v2(&tri.t[0], &tri.t[1]);
	}
	if (tri.p[2].y < tri.p[0].y)
	{
		swap_v(&tri.p[0], &tri.p[2]);
		swap_v2(&tri.t[0], &tri.t[2]);
	}
	if (tri.p[2].y < tri.p[1].y)
	{
		swap_v(&tri.p[1], &tri.p[2]);
		swap_v2(&tri.t[1], &tri.t[2]);
	}
	return (tri);
}

void		apply_texture(t_tex_var *var, t_texture tex, t_depth *depth)
{
	int r;
	int g;
	int b;

	depth[(var->i << 9) + (var->i << 8) + (var->i << 5) +\
		var->j].w = var->tex_w;
	if (var->noc == 0)
		depth[(var->i << 9) + (var->i << 8) + (var->i << 5) +\
			var->j].color = tex.pixels[var->tex_y][var->tex_x];
	else
	{
		r = 0.2126 * (tex.pixels[var->tex_y][var->tex_x] >> 16 & 255);
		g = 0.7152 * (tex.pixels[var->tex_y][var->tex_x] >> 8 & 255);
		b = 0.0722 * (tex.pixels[var->tex_y][var->tex_x] >> 0 & 255);
		depth[(var->i << 9) + (var->i << 8) + (var->i << 5) +\
			var->j].color = (r * 256 * 256) + (g * 256) + b;
	}
}
