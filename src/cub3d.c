/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajorge-p <ajorge-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 10:13:39 by ajorge-p          #+#    #+#             */
/*   Updated: 2024/12/12 13:03:32 by ajorge-p         ###   ########.fr       */
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
	cube->c_color = get_color(file, "C");
	cube->map = fill_map(file);
	cube->map_col = check_map_coluns(cube->map);
	cube->map_line = search_for_big_line(cube->map);
	get_player_position(cube);
	cube->rff_map = fill_rff_map(cube->map);
	rff_check(cube, 0, 0);
	cube->win = mlx_new_window(cube->mlx, map_W, map_H, "Cub3D");
	return(cube);
}

int main(int ac, char **av)
{
	t_cube *cube;
	check_errors(ac, av);
	
	cube = init_cube(av[1]);
	
	//print_map(cube->map);
	mlx_hook(cube->win, 17, 0, close_cube, cube);
	draw_floor(cube);
	draw_ceiling(cube);
	put_square(cube, map_W/2, map_H-50);
	mlx_key_hook(cube->win, key_press, cube);
	mlx_loop(cube->mlx);
}