/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajorge-p <ajorge-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 11:12:59 by ajorge-p          #+#    #+#             */
/*   Updated: 2025/01/27 18:27:49 by ajorge-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"


void create_pixel_map(t_data *data)
{
	int i;

	data->pixel_map = safe_calloc(sizeof(int *), SCREEN_H + 1);
	i = -1;
	while(++i < SCREEN_H)
	{
		data->pixel_map[i] = ft_calloc(sizeof(int), SCREEN_W);
		if(!data->pixel_map[i])
			print_error("Error on Pixel Map\n");
	}
}

int  get_cardinal_direction(t_ray *ray)
{
	if(ray->side == 0)
	{
		if(ray->ray_dir_x < 0)
			return (W);
		else
			return (E);
	}	
	else
	{
		if(ray->ray_dir_y > 0)
			return (S);
		else 
			return (N);
	}
}

void update_pixel_map(t_data *data, t_ray *ray, int x)
{
	int	dir;
	double step;
	double pos;
	int color;
	
	dir = get_cardinal_direction(ray);
	ray->text_x = (int)(ray->wall_x * TILE_SIZE);
	if(dir == W || dir == S)
		ray->text_x = TILE_SIZE - ray->text_x - 1;
	step = (double)TILE_SIZE / ray->wall_height;
	pos = (ray->start_pos_draw - SCREEN_H / 2 + ray->wall_height / 2) * step;
	while(ray->start_pos_draw < ray->end_pos_draw)
	{
		pos += step;
		color = (data->texture_buffer[dir][TILE_SIZE * ((int)pos & (TILE_SIZE - 1)) + ray->text_x]);
		if(dir == N || dir == S)
			color = (color >> 1) & 0x7F7F7F;
		if(color > 0)
			data->pixel_map[ray->start_pos_draw][x] = color;
		ray->start_pos_draw++;
	}
}

void	draw_pixel_map(t_cube *cube, t_data *data)
{
	t_img 	img;
	int 	x;
	int 	y;

	img.img = mlx_new_image(cube->mlx,SCREEN_W, SCREEN_H);
	if(!img.img)
		return ;
	img.addr = (int *)mlx_get_data_addr(img.img, &img.bytes_per_pixel, &img.line_len, &img.endian);
	y = -1;
	while(++y < SCREEN_H)
	{
		x = -1;
		while(++x < SCREEN_W)
		{
			//printf("pixel_map[%d][%d] = %d\n", y, x, data->pixel_map[y][x]);
			if(data->pixel_map[y][x] > 0)
				img.addr[y * (img.line_len / 4) + x] = data->pixel_map[y][x];
			else if(y < SCREEN_H / 2)
				img.addr[y * (img.line_len / 4) + x] = data->c_color->hex_color;
			else if(y < SCREEN_H - 1)
				img.addr[y * (img.line_len / 4) + x] = data->f_color->hex_color;
		}
	}
	mlx_put_image_to_window(cube->mlx, cube->win, img.img, 0, 0);
	mlx_destroy_image(cube->mlx, img.img);
}