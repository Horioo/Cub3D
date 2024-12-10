/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajorge-p <ajorge-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 11:14:15 by ajorge-p          #+#    #+#             */
/*   Updated: 2024/12/10 11:14:44 by ajorge-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static int		conv_ex(int nb)
{
	if (nb >= 10)
		return (nb - 10 + 'a');
	else
		return (nb + '0');
}

char	*itoa_base(int value, int base)
{
	int					i;
	char				*str;
	int				tmp;
	
	i = 0;
	tmp = value;
	while (tmp >= base)
	{
		tmp = tmp / base;
		i++;
	}	
	if (!(str = (char *)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	str[i + 1] = '\0';
	while (i >= 0)
	{
		tmp = value % base;
		str[i] = conv_ex(tmp);
		value /= base;
		i--;
	}
	return (str);
}

int	get_hex_color(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}


//Fazer com que ele leia as linhas do F e C e obter o valor para dentro da struct t_color
//Fazer o split da virgula!!!!! Joao e um Deus do codigo, fuck minishell
//Mudei o atoi do libft para dar return a 666 quando a string enviada e nula
void get_rgb(char *line, t_color *s_color)
{
	char **color;
	
	color = ft_split(line, ',');
	if(!color)
		return ;
	s_color->red = ft_atoi(color[0]);
	s_color->green = ft_atoi(color[1]);
	s_color->blue = ft_atoi(color[2]);
	if(s_color->red > 255 || s_color->green > 255 || s_color->blue > 255)
	{
		//print_error("Some color didnt get a value\n");
		printf("Some color didnt get a correct value\n");
		exit(1);
	}
	s_color->hex_color = get_hex_color(s_color->red,s_color->green, s_color->blue);
}

t_color *get_color(char *file, char *type)
{
	char *row;
	t_color *color;
	int fd;

	color = malloc(sizeof(t_color));
	if(!color)
		return (NULL);
	fd = open(file, O_RDONLY);
	row = get_next_line(-1);
	row = get_next_line(fd);
	while(row)
	{
		if(strncmp(row, type, 1) == 0)
			get_rgb(row + 2, color);
		free(row);
		row = get_next_line(fd);
	}
	free(row);
	return (color);
}
