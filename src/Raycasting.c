/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajorge-p <ajorge-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 11:28:34 by ajorge-p          #+#    #+#             */
/*   Updated: 2025/01/10 13:46:06 by ajorge-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void calculate_dist(t_ray *ray, t_player *player)
{
	if(ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (player->p_x - ray->map_x) * ray->delta_dist_x; 
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1 - player->p_x) * ray->delta_dist_x;
	}
	if(ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (player->p_y - ray->map_y) * ray->delta_dist_y; 
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1 - player->p_y) * ray->delta_dist_y;
	}
}

void raycaster_var_init(t_ray *ray, t_player *player, int x)
{
	ray->camera_x = 2 * x / (double)SCREEN_W - 1;
	ray->ray_dir_x = player->dir_x + player->plane_x * ray->camera_x;
	ray->ray_dir_y = player->dir_y + player->plane_y * ray->camera_x;
	ray->map_x = player->p_x;
	ray->map_y = player->p_x;
	ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
	ray->delta_dist_y = fabs(1 / ray->ray_dir_y);	
}

// Digital Differential Analysis
void DDA(t_ray *ray, t_data *data)
{
	while(1)
	{
		if(ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if(data->map[ray->map_x][ray->map_y] == '1')
			break;
	}
	if(ray->side == 0)
		ray->wall_dist = ray->side_dist_x - ray->delta_dist_x;
	else
		ray->wall_dist = ray->side_dist_y - ray->delta_dist_y;
}

void wall_calculations(t_ray *ray, t_player *player)
{
	ray->wall_height = (int)(SCREEN_H / ray->wall_dist);
	ray->start_pos_draw = -ray->wall_height / 2 + SCREEN_H / 2;
	if(ray->start_pos_draw < 0)
		ray->start_pos_draw = 0;
	ray->end_pos_draw = ray->wall_height / 2 + SCREEN_H / 2;
	if(ray->end_pos_draw >= SCREEN_H)
		ray->end_pos_draw = SCREEN_H - 1;
	if(ray->side == 0)
		ray->wall_x = player->p_y + ray->wall_dist * ray->ray_dir_y;
	else
		ray->wall_x = player->p_x + ray->wall_dist * ray->ray_dir_x;
	ray->wall_x -= floor(ray->wall_x);
}

bool create_pixel_map(t_data *data)
{
	int i;

	data->pixel_map = safe_calloc(sizeof(int *), SCREEN_H + 1);
	i = -1;
	while(++i < SCREEN_H)
	{
		data->pixel_map[i] = ft_calloc(sizeof(int), SCREEN_W);
		if(!data->pixel_map[i])
			return(/*(Free pixel_map array),*/ false);
	}
	return (true);
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
	step = TILE_SIZE / ray->wall_height;
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

void Raycaster(t_cube *cube)
{ 
	int x;

	x = 0;
	while(x < SCREEN_W)
	{
		raycaster_var_init(cube->ray, cube->player, x);
		calculate_dist(cube->ray, cube->player);
		DDA(cube->ray, cube->data);
		wall_calculations(cube->ray, cube->player);
		update_pixel_map(cube->data, cube->ray, x);
		x++;
	}	
} 