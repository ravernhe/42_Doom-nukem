/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravernhe <ravernhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 17:25:22 by ravernhe          #+#    #+#             */
/*   Updated: 2020/03/09 12:30:37 by ravernhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

void	init_move(t_move *move)
{
	move->jump = 0;
	move->crouch = 0;
	move->fly = 1;
	move->velocity = 1;
	move->speed = SPEED;
	move->gravity = 0.07f;
	move->dy = 0.02f;
	move->flag = 0;
}

void	get_move(t_move *move, const Uint8 *keys)
{
	if (keys[SDL_SCANCODE_SPACE] == 1 && move->jump == 0)
		move->jump = 1;
	if (keys[SDL_SCANCODE_C] == 1)
		move->crouch = 1;
	if (keys[SDL_SCANCODE_LCTRL] == 1)
		move->velocity = 2.0f;
	else
		move->velocity = 1.0f;
}

void	gravity_fall(t_env *env, t_move *move)
{
	if (collide(env, env->vcamera, 1, move->dy) == 0 && move->jump != 2)
	{
		move->jump = 3;
		env->vcamera.y -= move->dy;
		if (move->dy < 4.5f)
			move->dy += move->gravity;
	}
	else if (collide(env, env->vcamera, 1, move->dy) == 1 && move->jump != 2)
	{
		move->dy = 0.02f;
		move->jump = 0;
	}
}

void	jumping(t_env *env, t_move *move)
{
	if (move->jump == 2)
	{
		if (move->dy >= 0.1f && collide(env, env->vcamera, 2, move->dy) == 0)
		{
			if (Mix_PlayChannel(-1, env->mix.jump, 0) == -1)
				ft_exit("music error");
			env->vcamera.y += move->dy;
			move->dy /= 2;
		}
		else
			move->jump = 3;
	}
	if (move->jump == 1 && collide(env, env->vcamera, 2, 3.9375f) == 0)
	{
		move->dy = 2;
		env->vcamera.y += move->dy;
		move->jump = 2;
	}
	else
		gravity_fall(env, move);
}

void	physic(t_env *env, t_move *move, const Uint8 *keys)
{
	t_vec3d	vright;
	t_vec3d	vforward;

	if (env->dy == 1)
	{
		move->dy = 0.2;
		env->dy = 0;
	}
	if (move->fly == -1)
		fly(env, move, keys);
	else
	{
		jumping(env, move);
		crouching(env, move, keys);
		vright = vec_mul(env->vlookright, move->speed * move->velocity);
		vforward = vec_mul(env->vlookdir, move->speed * move->velocity);
		move_forw(keys, vforward, env, move);
		move_side(keys, vright, env, move);
	}
}
