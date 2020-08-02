/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_tools_4.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravernhe <ravernhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 17:25:22 by ravernhe          #+#    #+#             */
/*   Updated: 2020/03/09 12:30:37 by ravernhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

float	get_third(float d1, float d2, t_tri tri)
{
	float	tmp;
	float	dist[3];

	dist[0] = ft_dist(tri.p[0], tri.p[1]);
	dist[1] = ft_dist(tri.p[0], tri.p[2]);
	dist[2] = ft_dist(tri.p[2], tri.p[1]);
	tmp = fmax(dist[0], fmax(dist[1], dist[2]));
	return (get_dist(dist, tmp, d1, d2));
}

void	init_vol(t_vol *v, t_env *env, int i)
{
	v->lon = ft_dist(env->tri[i].p[0], env->tri[i].p[1]);
	v->lar = ft_dist(env->tri[i].p[0], env->tri[i].p[2]);
	v->hau = ft_dist(env->tri[i].p[1], env->tri[i].p[2]);
	v->tmp = fmax(v->lon, fmax(v->lar, v->hau));
	if (v->lon == v->tmp)
		v->lon = 0.0f;
	else if (v->lar == v->tmp)
		v->lar = 0.0f;
	else if (v->hau == v->tmp)
		v->hau = 0.0f;
}

float	get_dist(float *dist, float tmp, float d1, float d2)
{
	if (dist[0] == tmp)
	{
		if (dist[1] != 0.0f && dist[1] != d1 && dist[1] != d2)
			return (dist[1]);
		if (dist[2] != 0.0f && dist[2] != d1 && dist[2] != d2)
			return (dist[2]);
		return (dist[1]);
	}
	else if (dist[1] == tmp)
	{
		if (dist[0] != 0.0f && dist[0] != d1 && dist[0] != d2)
			return (dist[0]);
		if (dist[2] != 0.0f && dist[2] != d1 && dist[2] != d2)
			return (dist[2]);
		return (dist[0]);
	}
	else if (dist[2] == tmp)
	{
		if (dist[0] != 0.0f && dist[0] != d1 && dist[0] != d2)
			return (dist[0]);
		if (dist[1] != 0.0f && dist[1] != d1 && dist[1] != d2)
			return (dist[1]);
		return (dist[0]);
	}
	return (0);
}

void	crouching(t_env *env, t_move *move, const Uint8 *keys)
{
	if (move->crouch == 1 && move->jump == 0)
	{
		env->crunch = 0.8f;
		move->crouch = 2;
		move->flag = 3;
		move->velocity = 0.3f;
	}
	else if (move->crouch == 2 && keys[SDL_SCANCODE_C] == 0 &&\
			collide(env, env->vcamera, 2, move->dy) == 0)
	{
		env->crunch = 0;
		move->crouch = 0;
		move->flag = 0;
		move->velocity = 1.0f;
	}
}

void	fly(t_env *env, t_move *move, const Uint8 *keys)
{
	t_vec3d	vright;
	t_vec3d	vforward;

	vright = vec_mul(env->vlookright, move->speed * 5);
	vforward = vec_mul(env->vlookdir, move->speed * 5);
	if (keys[SDL_SCANCODE_SPACE] == 1)
		env->vcamera.y += move->speed;
	if (keys[SDL_SCANCODE_C] == 1)
		env->vcamera.y -= move->speed;
	if (keys[SDL_SCANCODE_W] == 1)
		env->vcamera = vec_add(env->vcamera, vforward);
	if (keys[SDL_SCANCODE_S] == 1)
		env->vcamera = vec_sub(env->vcamera, vforward);
	if (keys[SDL_SCANCODE_A] == 1)
		env->vcamera = vec_add(env->vcamera, vright);
	if (keys[SDL_SCANCODE_D] == 1)
		env->vcamera = vec_sub(env->vcamera, vright);
	move->dy = 0.02f;
}
