/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world_gen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravernhe <ravernhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 17:25:22 by ravernhe          #+#    #+#             */
/*   Updated: 2020/03/09 12:31:09 by ravernhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

void	init_display(t_world *world, t_env *env)
{
	t_mat4x4	matcamrot;

	world->i = 0;
	world->matrotz = init_matrotz(0.0f);
	world->matrotx = init_matrotx(0.0f);
	world->mattrans = mat_maketrans(0.0f, env->crunch, 0.0f);
	world->matworld = mat_makeid();
	world->matworld = mat_multmat(world->matrotz, world->matrotx);
	world->matworld = mat_multmat(world->matworld, world->mattrans);
	init_vec(&world->vup, 0.0f, 1.0f, 0.0f);
	init_vec(&world->vtarget, 0.0f, 0.0f, 1.0f);
	init_vec(&world->vright, 1.0f, 0.0f, 0.0f);
	matcamrot = init_matroty(env->fyaw);
	env->vlookdir = mat_mulvec(matcamrot, world->vtarget);
	env->vlookright = mat_mulvec(matcamrot, world->vright);
	world->vtarget = vec_add(env->vcamera, env->vlookdir);
	world->matcam = mat_pointat(env->vcamera, world->vtarget, world->vup);
	world->matview = mat_quick_invert(world->matcam);
	world->matview = mat_multmat(world->matview, init_matrotx(-env->fpitch));
}

t_tri	prep_zclip(t_tri t_v, t_tri t_tr, t_clipz *clipz, t_world world)
{
	t_v = world_to_view(t_tr, t_v, world);
	init_vec(&(clipz->plane_p), 0.0f, 0.0f, 2.0f);
	init_vec(&(clipz->plane_n), 0.0f, 0.0f, 1.0f);
	clipz->n = 0;
	clipz->nclipped = tri_clipping(clipz->plane_p, clipz->plane_n,\
		t_v, clipz->clipped);
	return (t_v);
}

t_tri	*t_proj(t_clipz *clipz, t_tri *t_pj, t_world *world, t_env *env)
{
	while (clipz->n < clipz->nclipped)
	{
		t_pj[world->d] = projection(t_pj[world->d], *clipz, env);
		t_pj[world->d] = scale_screen(t_pj[world->d]);
		clipz->n++;
		world->d++;
	}
	return (t_pj);
}

void	display(t_sdl *sdl, t_env *env)
{
	t_world	world;
	t_tri	tri_trans;
	t_tri	*tri_proj;
	t_tri	tri_view;
	t_clipz	clipz;

	world.d = 0;
	if (!(tri_proj = malloc(sizeof(t_tri) * (env->nb_tri * 5))))
		ft_exit("malloc error");
	init_display(&world, env);
	while (world.i < env->nb_tri)
	{
		tri_trans = trans_mat(tri_trans, &world, env);
		if (dot_product(world.normal, world.vcam_ray) < 0.0f)
		{
			tri_view = prep_zclip(tri_view, tri_trans, &clipz, world);
			tri_proj = t_proj(&clipz, tri_proj, &world, env);
		}
		world.i++;
	}
	tri_to_pixel(sdl, tri_proj, world.d, env);
	free(tri_proj);
	draw_stuff(sdl, env);
	SDL_RenderPresent(sdl->render);
}
