/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravernhe <ravernhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 17:25:22 by ravernhe          #+#    #+#             */
/*   Updated: 2020/03/09 12:45:03 by ravernhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

int		skip(char *str, int i)
{
	while (str[i] && str[i] > 32)
		i++;
	while (str[i] && str[i] <= 32)
		i++;
	return (i);
}

t_vec3d	p_vec(char *str, t_vec3d vec)
{
	int	i;

	i = 0;
	i = skip(str, i);
	vec.x = ft_atof(str + i);
	i = skip(str, i);
	vec.y = ft_atof(str + i);
	i = skip(str, i);
	vec.z = ft_atof(str + i);
	vec.w = 1.0f;
	return (vec);
}

t_tri	p_tri(char *str, t_tri tri, t_vec3d *list, t_vec2d *uv)
{
	int	i;

	i = 0;
	i = skip(str, i);
	tri.p[0] = list[ft_atoi(str + i) - 1];
	while (str[i] && str[i] >= '0' && str[i] <= '9')
		i++;
	if (str[i] == '/')
		tri.t[0] = uv[ft_atoi(str + i + 1) - 1];
	i = skip(str, i);
	tri.p[1] = list[ft_atoi(str + i) - 1];
	while (str[i] && str[i] >= '0' && str[i] <= '9')
		i++;
	if (str[i] == '/')
		tri.t[1] = uv[ft_atoi(str + i + 1) - 1];
	i = skip(str, i);
	tri.p[2] = list[ft_atoi(str + i) - 1];
	while (str[i] && str[i] >= '0' && str[i] <= '9')
		i++;
	if (str[i] == '/')
		tri.t[2] = uv[ft_atoi(str + i + 1) - 1];
	return (tri);
}

void	init_pars(t_env *env, t_pars *p, char *file_name)
{
	p->v[0] = 0;
	p->v[1] = 0;
	env->nb_obb = -1;
	env->nb_tex = 0;
	env->nb_tri = 0;
	p->m[0] = 1;
	p->m[1] = 1;
	p->m[2] = 1;
	p->o[0] = 1;
	if ((p->fd = open(file_name, O_RDONLY)) < 0)
		ft_exit("open file error");
	if (!(ft_strcmp(file_name, "obj_file/doom.obj")))
		env->tuto = 1;
	if (!(env->tex = malloc(sizeof(t_texture) * (1024))))
		ft_exit("malloc error");
	env->obb = NULL;
}

t_env	parse(char *file_name, t_env env, t_vec3d *list, t_vec2d *uv)
{
	t_pars	p;

	init_pars(&env, &p, file_name);
	while ((p.ret = get_next_line(p.fd, &p.buff)) == 1)
	{
		if (p.buff[0] == 'v' && p.buff[1] == 32)
			list = get_vec(&p, list, p.buff);
		else if (p.buff[0] == 's' && p.buff[1] == 'p' && p.buff[2] == 'a' && \
				p.buff[3] == 'w' && p.buff[4] == 'n')
			get_spawn(&env, p.buff);
		else if (p.buff[0] == 'v' && p.buff[1] == 't' && p.buff[2] == 32)
			uv = get_vec_tex(&p, uv, p.buff);
		else if (p.buff[0] == 'u' && p.buff[1] == 's' && p.buff[2] == 'e' && \
				p.buff[3] == 'm' && p.buff[4] == 't' && p.buff[5] == 'l' &&\
				p.buff[6] == 32)
			get_tex(&env, p.buff);
		else if (p.buff[0] == 'f' && p.buff[1] == 32)
			get_face(&env, &p, list, uv);
		else if (p.buff[0] == 'o' && p.buff[1] == 32)
			get_obb(&env, &p);
		else if (p.buff[0] == 'i' && p.buff[1] == 'd')
			env.obb[env.nb_obb].id = ft_atoi(p.buff + 3);
		free(p.buff);
	}
	return (end_pars(&env, list, uv, &p));
}
