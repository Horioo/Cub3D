/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajorge-p <ajorge-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 10:13:39 by ajorge-p          #+#    #+#             */
/*   Updated: 2024/11/08 11:32:49 by ajorge-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/cub3d.h"
#include <math.h>

void	map_check(t_cube *cube, int x, int y)
{
	(void)cube;
	(void)x;
	(void)y;
}


int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] && s2[i])
		i++;
	return (s1[i] - s2[i]);
}

int	colum_maps(char *file)
{
	int		cnt;
	char	*row;
	int		fd;

	cnt = 0;
	fd = open(file, O_RDONLY);
	row = get_next_line(fd);
	while (row)
	{
		free(row);
		row = get_next_line(fd);
		cnt++;
	}
	free(row);
	close(fd);
	return (cnt);
}

char	**fill_map(char *file)
{
	int		cnt;
	char	**map;
	char	*row;
	int		line;
	int		fd;

	cnt = colum_maps(file);
	map = malloc(sizeof(char *) * (cnt + 1));
	row = get_next_line(-1);
	fd = open(file, O_RDONLY);
	row = get_next_line(fd);
	line = 0;
	while (row)
	{
		map[line++] = ft_strtrim(row, "\n");
		free(row);
		row = get_next_line(fd);
	}
	free(row);
	map[line] = NULL;
	close(fd);
	return (map);
}

t_cube *init_cube(char *file)
{
	t_cube *cube;

	cube = malloc(sizeof(t_cube));
	if(!cube)
		return (NULL);
	cube->mlx = mlx_init();
	cube->map = fill_map(file);
	cube->win = mlx_new_window(cube->mlx, 1024, 480, "Cub3D");

	return(cube);
}

int	checkcub(char *file)
{
	int	len;

	len = ft_strlen(file);
	if (len > 4 && ft_strcmp(file + len - 4, ".cub") == 0)
		return (1);
	return (0);
}

void	print_error(char *str)
{
	printf("%s", str);
	exit (1);
}

void	check_errors(int ac, char **av)
{
	if(ac != 2)
		print_error("Error\nError on Arguments\n");
	if(!checkcub(av[1]))
		print_error("Error\nError on .cub\n");
	if(open(av[1], O_RDONLY) == -1)
		print_error("Error\nError on Opening file\n");
}

int	close_cube(t_cube *cube)
{
	(void)cube;
	//errormsg(cube, "Bye Bye >:)", 0);
	exit(0); //Remove later and uncomment errormsg()
	return (0);
}

// Desenhar as linhas de "visao" do player
// x e y sao a posicao atual do player
double degrees_to_radians(double degrees)
{
	return (degrees * (PI / 180.00));
}

//Dar fix ao drawing das linhas, matematica nao esta mathing
void draw_line(t_cube *cube, int x, int y, int end_x, int end_y)
{
	int dist_x;
	int dist_y;
	int steps;
	float x_increm;
	float y_increm;
	float new_x;
	float new_y;
	int i;
	
	dist_x = end_x - x;
	dist_y = end_y - y;
	steps = abs(dist_x) > abs(dist_y) ? abs(dist_x) : abs(dist_y);
	x_increm = dist_x / (float)steps;
	y_increm = dist_y / (float)steps;
	i = 0;
	new_x = x;
	new_y = y;
	while(i <= steps)
	{
		mlx_pixel_put(cube->mlx, cube->win, (int)new_x, (int)new_y, 0x00FFFF00);
		new_x += x_increm;
		new_y += y_increm;
		i++;
	}
}

void draw_lines(t_cube *cube, int x, int y)
{
	int i;
	int n_lines;
	int line_lenght;
	double angle;
	double radians;
	int end_x;
	int end_y;
	
	i = 0;
	n_lines = 50;
	line_lenght = 50;
	while(i <= n_lines)
	{
		angle = i - n_lines / 2;
		radians = degrees_to_radians(angle);
		end_x = x + (int)(line_lenght * cos(radians));
		end_y = y + (int)(line_lenght * sin(radians));
		draw_line(cube, x, y, end_x, end_y);
		i++;
	}
}

void put_square(t_cube *cube, int x, int y, int color)
{
	int n_lines;
	int n_rows;
	int n_pixels;

	n_lines = x;
	n_pixels = 50;
	while(n_lines <= x + n_pixels)
	{
		n_rows = y;
		while(n_rows <= y + n_pixels)
		{
			mlx_pixel_put(cube->mlx, cube->win,n_lines, n_rows, color);
			n_rows++;
		}
		n_lines++;
	}
	printf("x = %d\ny = %d\n", n_lines, n_rows - ((n_pixels + x) / 2));
	//Fazer com que enquanto ele nao bata numa parede "1" faca linhas, fazer de pouco a pouco
	draw_lines(cube, n_lines, (y + n_rows) / 2);
}

void print_map(t_cube *cube)
{
	int i;
	int j;
	
	i = 0;
	while(cube->map[i])
	{
		j = 0;
		printf("Linha %d: ", i);
		while(cube->map[i][j])
		{
			printf("%c", cube->map[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}

int key_press(int keycode, t_cube *cube)
{
	if(keycode == ESC)
		close_cube(cube);
	if (keycode != DOWN && keycode != UP && keycode != LEFT && keycode != RIGHT)
		return (1);
	return (0);
}
int main(int ac, char **av)
{
	t_cube *cube;
	check_errors(ac, av);
	
	cube = init_cube(av[1]);
	
	print_map(cube);
	put_square(cube, 50, 50, 0x00FF0000);
	mlx_hook(cube->win, 17, 0, close_cube, cube);
	mlx_key_hook(cube->win, key_press, cube);
	mlx_loop(cube->mlx);

}