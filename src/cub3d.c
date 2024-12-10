/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajorge-p <ajorge-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 10:13:39 by ajorge-p          #+#    #+#             */
/*   Updated: 2024/12/10 12:31:13 by ajorge-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

t_cube *init_cube(char *file)
{
	t_cube *cube;

	cube = malloc(sizeof(t_cube));
	if(!cube)
		return (NULL);
	cube->textures = get_textures(file);
	cube->f_color = get_color(file, "F");
	//printf("Floor Colors\nRed: %d Green: %d Blue: %d\n", cube->f_color->red, cube->f_color->green, cube->f_color->blue);
	cube->c_color = get_color(file, "C");
	//printf("Ceiling Colors\nRed: %d Green: %d Blue: %d\n", cube->c_color->red, cube->c_color->green, cube->c_color->blue);
	cube->mlx = mlx_init();
	cube->map = fill_map(file);
	get_player_position(cube);
	//printf("Player X = %d\nPlayer Y = %d\nLetra = %c\n", cube->player_x, cube->player_y, cube->map[cube->player_y][cube->player_x]);
	cube->rff_map = fill_rff_map(cube->map);
	cube->win = mlx_new_window(cube->mlx, map_W, map_H, "Cub3D");
	return(cube);
}

int main(int ac, char **av)
{
	t_cube *cube;
	check_errors(ac, av);
	
	cube = init_cube(av[1]);
	
	//print_map(cube->map);
	put_square(cube, map_W/2, map_H-50);
	mlx_hook(cube->win, 17, 0, close_cube, cube);
	mlx_key_hook(cube->win, key_press, cube);
	mlx_loop(cube->mlx);
}