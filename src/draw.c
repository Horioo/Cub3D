/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajorge-p <ajorge-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 11:12:59 by ajorge-p          #+#    #+#             */
/*   Updated: 2024/12/10 11:33:38 by ajorge-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

// Funcao para transformar em radians para depois ser possivel obter os angulos para fazer o cone de visao
double degrees_to_radians(double degrees)
{
	return (degrees * (PI / 180.00));
}

// Desenhar as linhas de "visao" do player
// x e y sao a posicao atual do player
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
		mlx_pixel_put(cube->mlx, cube->win, (int)new_x, (int)new_y, cube->f_color->hex_color);
		new_x += x_increm;
		new_y += y_increm;
		i++;
	}
}
//Funcao vai ter de ser refeita provavelmente, ela esta a fazer os raios mas esta com valores postos a mao
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
	line_lenght = map_H;
	while(i <= n_lines)
	{
		angle = i - n_lines * 2 - 15;
		radians = degrees_to_radians(angle);
		end_x = x + (int)(line_lenght * cos(radians));
		end_y = y + (int)(line_lenght * sin(radians));
		draw_line(cube, x-25, y, end_x-25, end_y);
		i++;
	}
}

void put_square(t_cube *cube, int x, int y)
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
			
			mlx_pixel_put(cube->mlx, cube->win,n_lines, n_rows, cube->c_color->hex_color);
			n_rows++;
		}
		n_lines++;
	}
	//Fazer com que enquanto ele nao bata numa parede "1" faca linhas, fazer de pouco a pouco
	draw_lines(cube, n_lines, y);
}
