/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rff.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajorge-p <ajorge-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 12:28:07 by ajorge-p          #+#    #+#             */
/*   Updated: 2024/12/12 13:12:32 by ajorge-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

//Verificar ChatGPT
void rff_check(t_cube *cube, int x, int y)
{
	printf("Entrou 1 y = %d   x = %d    %c\n", y, x, cube->rff_map[y][x]);
	if(!cube->rff_map || x < 0 || y < 0 || x >= cube->map_line + 1 || y >= cube->map_col + 1)
		return ;
	printf("Entrou 2\n");	
	if(cube->rff_map[y][x] == '1' || cube->rff_map[y][x] == 'z' || cube->rff_map[y][x] == ' ')
		return ;
	printf("Entrou 3\n");	
	if(cube->rff_map[y][x] == '0')
		print_error("Invalid Map\n");
	cube->rff_map[y][x] = '5';
	print_map(cube->rff_map);
	rff_check(cube, x + 1, y);
	rff_check(cube, x - 1, y);
	rff_check(cube, x, y + 1);
	rff_check(cube, x, y - 1);
}

