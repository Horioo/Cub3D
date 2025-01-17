/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajorge-p <ajorge-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 11:28:34 by ajorge-p          #+#    #+#             */
/*   Updated: 2025/01/17 12:28:27 by ajorge-p         ###   ########.fr       */
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
		ray->side_dist_x = (ray->map_x + 1.0 - player->p_x) * ray->delta_dist_x;
	}
	if(ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (player->p_y - ray->map_y) * ray->delta_dist_y; 
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - player->p_y) * ray->delta_dist_y;
	}
}

void raycaster_var_init(t_ray *ray, t_player *player,t_data *data, int x)
{
	ray->camera_x = 2 * x / (double)SCREEN_W - 1;
	ray->ray_dir_x = player->dir_x + player->plane_x * ray->camera_x;
	ray->ray_dir_y = player->dir_y + player->plane_y * ray->camera_x;
	ray->map_x = data->player_x;
	ray->map_y = data->player_y;
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
		if(data->map[ray->map_y][ray->map_x] > 0 )
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

void Raycaster(t_cube *cube)
{ 
	int x;

	x = 0;
	while(x < SCREEN_W)
	{
		raycaster_var_init(cube->ray, cube->player, cube->data,x);
		calculate_dist(cube->ray, cube->player);
		DDA(cube->ray, cube->data);
		wall_calculations(cube->ray, cube->player);
		update_pixel_map(cube->data, cube->ray, x);
		x++;
	}
} 