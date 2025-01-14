/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajorge-p <ajorge-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 10:13:39 by ajorge-p          #+#    #+#             */
/*   Updated: 2025/01/14 13:19:57 by ajorge-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	*safe_calloc(size_t type, size_t bytes)
{
	void	*ret;

	ret = ft_calloc(type, bytes);
	if (!ret)
		print_error("Error on Calloc\n");
	return (ret);
}

void	double_check_map(t_data *data)
{
	int i;
	int	j;

	i = 0;
	while(i < check_map_coluns(data->rff_map))
	{
		j = 0;
		while(j < ft_strlen(data->rff_map[i]))
		{
			if(data->rff_map[i][j + 1] && data->rff_map[i][j] == '0' && data->rff_map[i][j + 1] == ' ')
				print_error("Invalid Map, Space Found after a Open Space\n");
			j++;
		}
		i++;
	}
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
	double_check_map(data);
	create_pixel_map(data);
	return (data);
}

t_player *init_player(t_cube *cube)
{
	t_player *p;

	p = safe_calloc(sizeof(t_player), 1);
	
	p->p_x = cube->data->player_x + TILE_SIZE + TILE_SIZE / 2;
	p->p_y = cube->data->player_y + TILE_SIZE + TILE_SIZE / 2;
	p->fov_rd = (FOV * PI) / 180;
	p->angle = PI;
	return (p);
}

void game_start(t_data *data)
{
	t_cube *cube;

	cube = safe_calloc(sizeof(t_cube), 1);
	cube->data = data;
	cube->ray = safe_calloc(sizeof(t_ray), 1);
	cube->player = init_player(cube);
	cube->mlx = mlx_init();
	cube->win = mlx_new_window(cube->mlx, SCREEN_W, SCREEN_H, "Cub3D");
	mlx_hook(cube->win, 17, 0, close_cube, cube);
	//print_map(cube->map);
	//draw_floor(cube);
	//draw_ceiling(cube);
	//put_square(cube, SCREEN_W/2, SCREEN_H-50);
	print_map(data->map);
	Raycaster(cube);
	load_textures(cube, cube->data);
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