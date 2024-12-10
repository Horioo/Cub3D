/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajorge-p <ajorge-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 11:09:13 by ajorge-p          #+#    #+#             */
/*   Updated: 2024/12/10 12:31:25 by ajorge-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

//ToDo
void	map_check(t_cube *cube, int x, int y)
{
	(void)cube;
	(void)x;
	(void)y;
}

void print_map(char **map)
{
	int i;
	int j;
	
	i = 0;
	while(map[i] && map)
	{
		j = 0;
		//printf("Linha %d: ", i);
		while(map[i][j])
		{
			printf("%c", map[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}

int check_map_coluns(char **map)
{
	int i;

	i = 0;
	while(map[i])
		i++;
	return (i);
}

int search_for_big_line(char **map)
{
	int i;
	unsigned long line_lenght;
	
	i = 0;
	line_lenght = 0;
	while(map[i])
	{
		if(strlen(map[i]) > line_lenght)
			line_lenght = strlen(map[i]);
		i++;
	}
	return (line_lenght);
}

void	get_player_position(t_cube *cube)
{
	int x;
	int y;

	y = 0;
	while(cube->map[y])
	{
		x = 0;
		while(cube->map[y][x])
		{
			if(cube->map[y][x] == 'N' || cube->map[y][x] == 'E' || cube->map[y][x] == 'S' || cube->map[y][x] == 'W')
			{
				cube->player_x = x;
				cube->player_y = y;
			}
			x++;
		}
		y++;
	}
	if(cube->player_x == 0 && cube->player_y == 0)
		print_error("Error!!\nNo Player Detected\n");
}
