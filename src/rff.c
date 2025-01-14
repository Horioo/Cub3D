/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rff.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajorge-p <ajorge-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 12:28:07 by ajorge-p          #+#    #+#             */
/*   Updated: 2025/01/14 12:10:02 by ajorge-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void rff_check(t_data *data, int x, int y)
{
	if(!data->rff_map || x < 0 || y < 0 || x > data->map_W + 1 || y > data->map_H + 1)
		return ;
	if(data->rff_map[y][x] == '5' || data->rff_map[y][x] == '1')
		return ;
	if(data->rff_map[y][x] == '0')
		print_error("Invalid Map, Map Open on the borders\n");
	data->rff_map[y][x] = '5';
	rff_check(data, x + 1, y);
	rff_check(data, x, y + 1);
	rff_check(data, x - 1, y);
	rff_check(data, x, y - 1);
}

