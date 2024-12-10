/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajorge-p <ajorge-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 11:15:01 by ajorge-p          #+#    #+#             */
/*   Updated: 2024/12/10 11:15:21 by ajorge-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int key_press(int keycode, t_cube *cube)
{
	if(keycode == ESC)
		close_cube(cube);
	if (keycode != DOWN && keycode != UP && keycode != LEFT && keycode != RIGHT)
		return (1);
	return (0);
}
