/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rff.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajorge-p <ajorge-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 12:28:07 by ajorge-p          #+#    #+#             */
/*   Updated: 2025/01/27 17:30:27 by ajorge-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void check_borders(t_data *data, char **map, int y, int x)
{
	if(x < 0 || y < 0 || x >= data->map_W || y >= data->map_H)
		print_error("Invalid Map, Map Open on the borders\n");
	if(map[y][x] != '0')
		return;
	map[y][x] = 'Z';
	check_borders(data, map, y + 1, x);
	check_borders(data, map, y - 1, x);
	check_borders(data, map, y, x + 1);
	check_borders(data, map, y, x - 1);
}

void check_map(t_data *data)
{
	int y;
	int x;

	y = 0;
	while(y < data->map_H)
	{
		x = 0;
		while(x < data->map_W)
		{
			if(data->rff_map[y][x] == '0')
				check_borders(data, data->rff_map, y, x);
			x++;
		}
		y++;
	}
}


