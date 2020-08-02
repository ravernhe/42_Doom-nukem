/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_tools_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravernhe <ravernhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 17:25:22 by ravernhe          #+#    #+#             */
/*   Updated: 2020/03/09 12:30:37 by ravernhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

void	init_collide(t_coll *c, int flag, float speed, t_vec3d *cam)
{
	if (!(c->d_vec = malloc(sizeof(float) * 6)))
		ft_exit("malloc error");
	if (flag == 1)
		cam->y -= speed;
	else if (flag == 2)
		cam->y += speed;
}

void	move_forw(const Uint8 *keys, t_vec3d vforward, t_env *env, t_move *move)
{
	if (keys[SDL_SCANCODE_W] == 1)
	{
		init_vec(&env->movement, vforward.x, vforward.y, vforward.z);
		if (collide(env, vec_add(env->vcamera, vforward), move->flag, 0) == 0)
			env->vcamera = vec_add(env->vcamera, vforward);
	}
	if (keys[SDL_SCANCODE_S] == 1)
	{
		init_vec(&env->movement, -vforward.x, -vforward.y, -vforward.z);
		if (collide(env, vec_sub(env->vcamera, vforward), move->flag, 0) == 0)
			env->vcamera = vec_sub(env->vcamera, vforward);
	}
}

void	move_side(const Uint8 *keys, t_vec3d vright, t_env *env, t_move *move)
{
	if (keys[SDL_SCANCODE_A] == 1)
	{
		init_vec(&env->movement, vright.x, vright.y, vright.z);
		if (collide(env, vec_add(env->vcamera, vright), move->flag, 0) == 0)
			env->vcamera = vec_add(env->vcamera, vright);
	}
	if (keys[SDL_SCANCODE_D] == 1)
	{
		init_vec(&env->movement, -vright.x, -vright.y, -vright.z);
		if (collide(env, vec_sub(env->vcamera, vright), move->flag, 0) == 0)
			env->vcamera = vec_sub(env->vcamera, vright);
	}
}
