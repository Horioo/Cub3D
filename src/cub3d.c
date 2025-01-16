/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajorge-p <ajorge-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 10:13:39 by ajorge-p          #+#    #+#             */
/*   Updated: 2025/01/16 13:14:54 by ajorge-p         ###   ########.fr       */
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

void	create_texture_buffer(t_data *data)
{
	int i;
	
	data->texture_buffer = safe_calloc(sizeof(int*), 4);
	i = -1;
	while(++i < 4)
		data->texture_buffer[i] = safe_calloc(sizeof(int), 1);
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
	create_texture_buffer(data);
	create_pixel_map(data);
	return (data);
}

void	init_dir_plane_aux(t_player *p)
{
	if(p->start_dir == 'W')
	{
		p->dir_x = -1;
		p->dir_y = 0;
		p->plane_x = 0;
		p->plane_y = 0.66;
	}
}

void	init_dir_plane(t_player *p)
{
	if(p->start_dir == 'N')
	{
		p->dir_x = 0;
		p->dir_y = -1;
		p->plane_x = 0.66;
		p->plane_y = 0;
	}
	if(p->start_dir == 'S')
	{
		p->dir_x = 0;
		p->dir_y = 1;
		p->plane_x = -0.66;
		p->plane_y = 0;
	}
	if(p->start_dir == 'E')
	{
		p->dir_x = 1;
		p->dir_y = 0;
		p->plane_x = 0;
		p->plane_y = 0.66;
	}
	init_dir_plane_aux(p);
}

t_player *init_player(t_data *data)
{
	t_player *p;

	p = safe_calloc(sizeof(t_player), 1);
	
	p->start_dir = data->map[data->player_y][data->player_x];
	p->p_x = data->player_x + TILE_SIZE + TILE_SIZE / 2;
	p->p_y = data->player_y + TILE_SIZE + TILE_SIZE / 2;
	p->fov_rd = (FOV * PI) / 180;
	p->angle = PI;
	p->movespeed = PLAYER_SPEED;
	p->rotation_speed = ROTATION_SPEED;
	init_dir_plane(p);
	return (p);
}

int	 game_loop(t_cube *cube)
{
	if(!cube->win)
		return (0);
	move_player(cube->data, cube->player);
	Raycaster(cube);
	load_textures(cube, cube->data);
	draw_pixel_map(cube, cube->data);
	return (0);
}

void game_start(t_data *data)
{
	t_cube *cube;

	cube = safe_calloc(sizeof(t_cube), 1);
	cube->data = data;
	cube->ray = safe_calloc(sizeof(t_ray), 1);
	cube->player = init_player(cube->data);
	cube->mlx = mlx_init();
	cube->win = mlx_new_window(cube->mlx, SCREEN_W, SCREEN_H, "Cub3D");	
	print_map(data->map);
	mlx_hook(cube->win, 17, 0, close_cube, cube);
	mlx_hook(cube->win, 2, 0, key_press, cube);
	mlx_hook(cube->win, 3, 0, key_release, cube);
	mlx_loop_hook(cube->mlx, game_loop, cube);
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