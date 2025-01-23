/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajorge-p <ajorge-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 12:33:23 by ajorge-p          #+#    #+#             */
/*   Updated: 2025/01/17 12:14:13 by ajorge-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	move_forward(t_data *data, t_player *p)
{
	double	x;
	double	y;

	x = p->p_x + p->dir_x * p->movespeed;
	y = p->p_y + p->dir_y * p->movespeed;
	if(x < 0)
		x = 0;
	if (y < 0)
		y = 0;
	if(data->pixel_map[p->p_y][(int)x] == 0)
		p->p_x += p->dir_x * p->movespeed;
	if(data->pixel_map[(int)y][p->p_x] == 0)
		p->p_y += p->dir_y * p->movespeed;
	if(p->p_x < 0)
		p->p_x = 0;
	if(p->p_y < 0)
		p->p_y = 0;

}

void	move_backward(t_data *data, t_player *p)
{
	double	x;
	double	y;

	x = p->p_x - p->dir_x * p->movespeed;
	y = p->p_y - p->dir_y * p->movespeed;
	if(x < 0)
		x = 0;
	if (y < 0)
		y = 0;
	if(data->pixel_map[p->p_y][(int)x] == 0)
		p->p_x -= p->dir_x * p->movespeed;
	if(data->pixel_map[(int)y][p->p_x] == 0)
		p->p_y -= p->dir_y * p->movespeed;
	if(p->p_x < 0)
		p->p_x = 0;
	if(p->p_y < 0)
		p->p_y = 0;
}

void	move_right(t_player *p)
{
	double	prev_dir_x;
	double	prev_plane_x;
	
	prev_dir_x = p->dir_x;
	prev_plane_x = p->plane_x;
	p->dir_x = p->dir_x * cos(p->rotation_speed) - p->dir_y * sin(p->rotation_speed);
	p->dir_y = prev_dir_x * sin(p->rotation_speed) + p->dir_y * cos(p->rotation_speed);
	p->plane_x = p->plane_x * cos(p->rotation_speed) - p->plane_y * sin(p->rotation_speed);
	p->plane_y = prev_plane_x * sin(p->rotation_speed) + p->plane_y * cos(p->rotation_speed);
}

void	move_left(t_player *p)
{
	double	prev_dir_x;
	double	prev_plane_x;
	
	prev_dir_x = p->dir_x;
	prev_plane_x = p->plane_x;
	p->dir_x = p->dir_x * cos(-p->rotation_speed) - p->dir_y * sin(-p->rotation_speed);
	p->dir_y = prev_dir_x * sin(-p->rotation_speed) + p->dir_y * cos(-p->rotation_speed);
	p->plane_x = p->plane_x * cos(-p->rotation_speed) - p->plane_y * sin(-p->rotation_speed);
	p->plane_y = prev_plane_x * sin(-p->rotation_speed) + p->plane_y * cos(-p->rotation_speed);
}

void	move_player(t_data *data, t_player *p)
{
	if(p->m_backward && p->is_moving)
		move_backward(data, p);
	if(p->m_forward && p->is_moving)
		move_forward(data, p);
	if(p->m_left && p->is_moving)
		move_left(p);
	if(p->m_right && p->is_moving)
		move_right(p);
}

