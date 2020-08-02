/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_thread_tools_2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravernhe <ravernhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 17:25:22 by ravernhe          #+#    #+#             */
/*   Updated: 2020/03/09 12:33:13 by ravernhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

void	clip_thread(t_draw_worker *arg)
{
	arg->tmp_tri = after_clip(arg->tri_proj, arg->start, &arg->end);
}

t_tri	*join_tri(t_tri *n_tri, int i, int *d, t_draw_worker *arg)
{
	if (i == 0)
		n_tri = tri_mem_join(n_tri, arg[i].tmp_tri, 0, arg[i].end);
	else
		n_tri = tri_mem_join(n_tri, arg[i].tmp_tri, *d, arg[i].end);
	*d += arg[i].end;
	return (n_tri);
}

void	add_tri(int *d, int *i, int nb_thread, t_draw_worker *arg)
{
	*i += 1;
	*d = 0;
	while (*i < nb_thread)
	{
		*d += arg[*i].end;
		*i += 1;
	}
}

t_tri	*alloc_n_tri(t_tri **n_tri, int *d, int *i)
{
	if (!(*n_tri = malloc(sizeof(t_tri) * (*d))))
		ft_exit("malloc error");
	*d = 0;
	*i = -1;
	return (*n_tri);
}

t_tri	*do_thread(t_tri *tri_proj, int *d, int nb_thread)
{
	pthread_t		thread[nb_thread];
	t_draw_worker	arg[nb_thread];
	t_thvar			t;

	t.i = -1;
	while (++t.i < nb_thread)
	{
		arg[t.i] = (t_draw_worker)
		{
			.tri_proj = tri_proj,
				.tmp_tri = NULL,
				.start = t.i * (*d) / nb_thread,
				.end = (t.i + 1) * (*d) / nb_thread
		};
		if ((t.ret = pthread_create(&thread[t.i], NULL,\
			(void *)clip_thread, arg + t.i)) == -1)
			ft_exit("malloc error");
	}
	while (t.i--)
		pthread_join(thread[t.i], NULL);
	add_tri(d, &t.i, nb_thread, arg);
	t.n_tri = alloc_n_tri(&t.n_tri, d, &t.i);
	while (++t.i < nb_thread)
		t.n_tri = join_tri(t.n_tri, t.i, d, arg);
	return (t.n_tri);
}
