/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajorge-p <ajorge-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 11:15:01 by ajorge-p          #+#    #+#             */
/*   Updated: 2025/01/17 11:46:59 by ajorge-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int key_press(int keycode, t_cube *cube)
{
	cube->player->is_moving = true;
	if(keycode == ESC)
		close_cube(cube);
	if(keycode == DOWN)
		cube->player->m_backward = true;
	if(keycode == UP)
		cube->player->m_forward = true;
	if(keycode == LEFT)
		cube->player->m_left = true;
	if(keycode == RIGHT)
		cube->player->m_right = true;
	return (0);
}

int key_release(int keycode, t_cube *cube)
{
	cube->player->is_moving = false;
	if(keycode == DOWN)
		cube->player->m_backward = false;
	if(keycode == UP)
		cube->player->m_forward = false;
	if(keycode == LEFT)
		cube->player->m_left = false;
	if(keycode == RIGHT)
		cube->player->m_right = false;
	return (0);
}
