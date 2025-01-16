/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajorge-p <ajorge-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 12:33:23 by ajorge-p          #+#    #+#             */
/*   Updated: 2025/01/16 13:07:09 by ajorge-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	move_forward(t_data *data, t_player *p)
{
	double	x;
	double	y;

	if(p->is_moving)
	{
		x = p->p_x + p->dir_x * p->movespeed;
		y = p->p_y + p->dir_y * p->movespeed;
		if(data->pixel_map[p->p_y][(int)x] == 0)
			p->p_x += p->dir_x * p->movespeed;
		if(data->pixel_map[(int)y][p->p_x] == 0)
			p->p_y += p->dir_y * p->movespeed;
		p->is_moving = false;
	}
}

void	move_backward(t_data *data, t_player *p)
{
	double	x;
	double	y;

	if(p->is_moving)
	{
		x = p->p_x - p->dir_x * p->movespeed;
		y = p->p_y - p->dir_y * p->movespeed;
		if(data->pixel_map[p->p_y][(int)x] == 0)
			p->p_x -= p->dir_x * p->movespeed;
		if(data->pixel_map[(int)y][p->p_x] == 0)
			p->p_y -= p->dir_y * p->movespeed;
		p->is_moving = false;
	}
}

void	move_right(t_player *p)
{
	double	prev_dir_x;
	double	prev_plane_x;
	
	if(p->is_moving)
	{
		prev_dir_x = p->dir_x;
		prev_plane_x = p->plane_x;
		p->dir_x = p->dir_x * cos(p->rotation_speed) - p->dir_y * sin(p->rotation_speed);
		p->dir_y = prev_dir_x * sin(p->rotation_speed) + p->dir_y * cos(p->rotation_speed);
		p->plane_x = p->plane_x * cos(p->rotation_speed) - p->plane_y * sin(p->rotation_speed);
		p->plane_y = prev_plane_x * sin(p->rotation_speed) + p->plane_y * cos(p->rotation_speed);
		p->is_moving = false;
	}
}

void	move_left(t_player *p)
{
	double	prev_dir_x;
	double	prev_plane_x;
	
	if(p->is_moving)
	{
		prev_dir_x = p->dir_x;
		prev_plane_x = p->plane_x;
		p->dir_x = p->dir_x * cos(-p->rotation_speed) - p->dir_y * sin(-p->rotation_speed);
		p->dir_y = prev_dir_x * sin(-p->rotation_speed) + p->dir_y * cos(-p->rotation_speed);
		p->plane_x = p->plane_x * cos(-p->rotation_speed) - p->plane_y * sin(-p->rotation_speed);
		p->plane_y = prev_plane_x * sin(-p->rotation_speed) + p->plane_y * cos(-p->rotation_speed);
		p->is_moving = false;
	}
}

void	move_player(t_data *data, t_player *p)
{
	if(p->m_backward)
		move_backward(data, p);
	if(p->m_forward)
		move_forward(data, p);
	if(p->m_left)
		move_left(p);
	if(p->m_right)
		move_right(p);
}

