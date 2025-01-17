/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajorge-p <ajorge-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 11:12:03 by ajorge-p          #+#    #+#             */
/*   Updated: 2025/01/15 12:28:41 by ajorge-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

char **get_textures(char *file)
{
	char *row;
	char **textures;
	int fd;
	int text_counter;

	text_counter = 0;
	textures = malloc((sizeof(char *) * 4) + 1);
	row = get_next_line(-1);
	fd = open(file, O_RDONLY);
	row = get_next_line(fd);
	while(row && text_counter < 4)
	{
		if(strncmp(row,"NO", 2) == 0)
			textures[N] = strdup(ft_strtrim(row,"\n") + 3);
		else if(strncmp(row,"EA", 2) == 0)
			textures[E] = strdup(ft_strtrim(row,"\n") + 3);
		else if(strncmp(row,"SO", 2) == 0)
			textures[S] = strdup(ft_strtrim(row,"\n") + 3);
		else if(strncmp(row,"WE", 2) == 0)
			textures[W] = strdup(ft_strtrim(row,"\n") + 3);
		text_counter++;
		free(row);
		row = get_next_line(fd);
	}
	return (textures);
}

void	img_to_texture_buff(t_data *data, t_img *img, int dir)
{
	int	*pixels;
	int	i;
	int	j;

	pixels = safe_calloc(sizeof(int), img->width * img->height);
	i = -1;
	while(++i < img->height)
	{
		j = -1;
		while(++j < img->width)
			pixels[i * img->width + j] = img->addr[i * img->width + j];
	}
	data->texture_buffer[dir] = pixels;
}

void	load_textures(t_cube *cube, t_data *data)
{
	t_img 	tmp;
	int		i;

	i = -1;
	while(++i < 4)
	{	
		tmp.img = mlx_xpm_file_to_image(cube->mlx, data->textures[i], &tmp.width, &tmp.height);
		if(!tmp.img)
			print_error("Error on file to image\n");
		tmp.addr = (int *)mlx_get_data_addr(tmp.img, &tmp.bytes_per_pixel, &tmp.line_len, &tmp.endian);
		if(!tmp.addr)
			printf("Error on get data Addr\n");
		img_to_texture_buff(data, &tmp, i);
		mlx_destroy_image(cube->mlx, tmp.img);
	}
}
