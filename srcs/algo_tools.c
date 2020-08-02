/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravernhe <ravernhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 17:25:22 by ravernhe          #+#    #+#             */
/*   Updated: 2020/03/08 18:58:55 by ravernhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

void		swap_v(t_vec3d *v1, t_vec3d *v2)
{
	t_vec3d tmp;

	tmp = *v1;
	*v1 = *v2;
	*v2 = tmp;
}

void		swap_v2(t_vec2d *v1, t_vec2d *v2)
{
	t_vec2d tmp;

	tmp = *v1;
	*v1 = *v2;
	*v2 = tmp;
}

void		swap_t(t_tri *t1, t_tri *t2)
{
	t_tri tmp;

	tmp = *t1;
	*t1 = *t2;
	*t2 = tmp;
}

void		swap_f(float *v1, float *v2)
{
	float tmp;

	tmp = *v1;
	*v1 = *v2;
	*v2 = tmp;
}

void		swap_i(int *v1, int *v2)
{
	int tmp;

	tmp = *v1;
	*v1 = *v2;
	*v2 = tmp;
}
