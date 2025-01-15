/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajorge-p <ajorge-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 12:33:23 by ajorge-p          #+#    #+#             */
/*   Updated: 2025/01/15 12:54:29 by ajorge-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	move_forward(t_data *data, t_player *p)
{
	double	x;
	double	y;

	x = p->p_x + p->dir_x * p->movespeed;
	y = p->p_y + p->dir_y * p->movespeed;
	if(data->pixel_map[p->p_y][(int)x] == 0)
		p->p_x += p->dir_x * p->movespeed;
	if(data->pixel_map[(int)y][p->p_x] == 0)
		p->p_y += p->dir_y * p->movespeed;
}

