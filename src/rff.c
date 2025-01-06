/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rff.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajorge-p <ajorge-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 12:28:07 by ajorge-p          #+#    #+#             */
/*   Updated: 2025/01/06 17:42:57 by ajorge-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

//Verificar ChatGPT
void rff_check(t_cube *cube, int x, int y)
{
	if(!cube->rff_map || x < 0 || y < 0 || x > cube->map_line + 1 || y > cube->map_col + 1)
		return ;
	if(cube->rff_map[y][x] == '5' || cube->rff_map[y][x] == '1')
		return ;
	if(cube->rff_map[y][x] == '0')
		print_error("Invalid Map 404\n");
	cube->rff_map[y][x] = '5';
	rff_check(cube, x + 1, y);
	rff_check(cube, x, y + 1);
	rff_check(cube, x - 1, y);
	rff_check(cube, x, y - 1);
}

