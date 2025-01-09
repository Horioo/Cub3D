/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajorge-p <ajorge-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 10:13:39 by ajorge-p          #+#    #+#             */
/*   Updated: 2025/01/09 12:43:25 by ajorge-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	*safe_malloc(size_t bytes)
{
	void	*ret;

	ret = malloc(bytes);
	if (!ret)
		print_error("Error on Malloc\n");
	return (ret);
}

t_data *init_data(char *file)
{
	t_data *data;
	
	data = malloc(sizeof(t_data));
	if(!data)
		return (NULL);
	data->textures = get_textures(file);
	data->f_color = get_color(file, "F");
	data->c_color = get_color(file, "C");
	data->map = fill_map(file);
	data->map_W = search_for_big_line(data->map);
	data->map_H = check_map_coluns(data->map);
	get_player_position(data);
	data->rff_map = fill_rff_map(data->map);
	rff_check(data, 1, 1);
	return (data);
}

t_player *init_player(t_cube *cube)
{
	t_player *p;

	p = safe_malloc(sizeof(t_player));
	
	p->p_x = cube->data->player_x + TILE_SIZE + TILE_SIZE / 2;
	p->p_y = cube->data->player_y + TILE_SIZE + TILE_SIZE / 2;
	p->fov_rd = (FOV * PI) / 180;
	p->angle = PI;
	return (p);
}

void game_start(t_data *data)
{
	t_cube *cube;

	cube = safe_malloc(sizeof(t_cube));
	cube->data = data;
	cube->ray = safe_malloc(sizeof(t_ray));
	cube->player = init_player(cube);
	cube->mlx = mlx_init();
	cube->win = mlx_new_window(cube->mlx, SCREEN_W, SCREEN_H, "Cub3D");
	mlx_hook(cube->win, 17, 0, close_cube, cube);
	//print_map(cube->map);
	draw_floor(cube);
	draw_ceiling(cube);
	put_square(cube, SCREEN_W/2, SCREEN_H-50);
	print_map(data->rff_map);
	//DDA(cube, map_W/2, map_H, map_H, 0);
	mlx_key_hook(cube->win, key_press, cube);
	mlx_loop(cube->mlx);
}



int main(int ac, char **av)
{
	t_data *data;

	check_errors(ac, av);
	data = init_data(av[1]);
	game_start(data);	
}