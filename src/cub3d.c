/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajorge-p <ajorge-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 10:13:39 by ajorge-p          #+#    #+#             */
/*   Updated: 2025/01/27 18:31:12 by ajorge-p         ###   ########.fr       */
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

int		check_four_direction(char **map, int i, int j)
{
	if(map[i][j + 1] && map[i][j + 1] == ' ')
		return (1);
	if(map[i][j - 1] && map[i][j - 1] == ' ')
		return (1);
	if(map[i + 1][j] && map[i + 1][j] == ' ')
		return (1);
	if(map[i - 1][j] && map[i - 1][j] == ' ')
		return (1);
	return (0);
}

void	double_check_map(t_data *data)
{
	int i;
	int	j;

	i = 0;
	while(i < check_map_coluns(data->map))
	{
		j = 0;
		while(j < ft_strlen(data->map[i]))
		{
			if(data->map[i][j] == '0' && check_four_direction(data->map, i, j))
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
	data->rff_map = fill_map(file);
	check_map(data);
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
	p->p_x = data->player_x * TILE_SIZE;
	p->p_y = data->player_y * TILE_SIZE;
	p->fov_rd = (FOV * PI) / 180;
	p->angle = PI;
	p->movespeed = PLAYER_SPEED;
	p->rotation_speed = ROTATION_SPEED;
	init_dir_plane(p);
	return (p);
}

void	render(t_cube *cube)
{
	create_pixel_map(cube->data);
	Raycaster(cube);
	load_textures(cube, cube->data);
	draw_pixel_map(cube, cube->data);
}

int	 game_loop(t_cube *cube)
{
	if(!cube->win)
		return (0);
	move_player(cube->data, cube->player);
	render(cube);
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
	render(cube);
	mlx_hook(cube->win, 17, 0, close_cube, cube);
	mlx_hook(cube->win, 2, (1L<<0), key_press, cube);
	mlx_hook(cube->win, 3, (1L<<1), key_release, cube);
	mlx_key_hook(cube->win, key_press, cube);
	mlx_key_hook(cube->win, key_release, cube);
	mlx_loop_hook(cube->mlx, game_loop, cube);
	mlx_loop(cube->mlx);
}

int main(int ac, char **av)
{
	t_data *data;

	check_errors(ac, av);
	data = init_data(av[1]);
	game_start(data);	
}