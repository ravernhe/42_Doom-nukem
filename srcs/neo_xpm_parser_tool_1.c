/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   neo_xmp_parser_tool_1.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravernhe <ravernhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 17:25:22 by ravernhe          #+#    #+#             */
/*   Updated: 2020/03/08 18:58:55 by ravernhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

void	xpm_header(t_texture *tex, t_tex_data *data, char *buff)
{
	int i;

	i = 1;
	tex->x = ft_atoi(buff + i);
	i = skip(buff, i);
	tex->y = ft_atoi(buff + i);
	i = skip(buff, i);
	data->nb_color = ft_atoi(buff + i);
	i = skip(buff, i);
	data->cpp = ft_atoi(buff + i);
	xpm_malloc(tex, data, -1);
}

int		hex_to_dec(char *hex)
{
	int dec;
	int len;
	int val;
	int i;

	i = 0;
	len = ft_strlen(hex) - 1;
	dec = 0;
	while (hex[i] != '\0')
	{
		if (hex[i] >= '0' && hex[i] <= '9')
			val = hex[i] - 48;
		else if (hex[i] >= 'a' && hex[i] <= 'f')
			val = hex[i] - 97 + 10;
		else if (hex[i] >= 'A' && hex[i] <= 'F')
			val = hex[i] - 65 + 10;
		dec += val * pow(16, len);
		len--;
		i++;
	}
	return (dec);
}

void	xpm_malloc(t_texture *tex, t_tex_data *data, int i)
{
	if (!(data->dico = malloc(sizeof(char *) * data->nb_color)))
		ft_exit("Error on a malloc");
	while (++i < data->nb_color)
	{
		if (!(data->dico[i] = malloc(sizeof(char) * data->cpp + 1)))
			ft_exit("Error on a malloc");
	}
	if (!(data->trad = malloc(sizeof(int) * data->nb_color)))
		ft_exit("Error on a malloc");
	if (!(data->alpha = malloc(sizeof(int) * data->nb_color)))
		ft_exit("Error on a malloc");
	if (!(tex->pixels = malloc(sizeof(int *) * tex->y)))
		ft_exit("Error on a malloc");
	if (!(tex->alphas = malloc(sizeof(int *) * tex->y)))
		ft_exit("Error on a malloc");
	i = -1;
	while (++i < tex->y)
	{
		if (!(tex->pixels[i] = malloc(sizeof(int) * tex->x)))
			ft_exit("Error on a malloc");
		if (!(tex->alphas[i] = malloc(sizeof(int) * tex->x)))
			ft_exit("Error on a malloc");
	}
}
