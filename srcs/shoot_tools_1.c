/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shoot_tools_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravernhe <ravernhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 17:25:22 by ravernhe          #+#    #+#             */
/*   Updated: 2020/03/09 12:30:37 by ravernhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

void	texture_portal2(t_obb *obb, t_env *env)
{
	int	i;
	int	q;

	i = 0;
	while (obb[i].id != 6)
		i++;
	q = obb[i].first;
	while (q <= obb[i].last)
	{
		env->tri[q].index = env->nb_tex - 14;
		q++;
	}
}
