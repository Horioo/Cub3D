/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajorge-p <ajorge-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 10:13:39 by ajorge-p          #+#    #+#             */
/*   Updated: 2024/11/26 13:15:26 by ajorge-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

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
	while(cnt != 8)
	{
		free(row);
		row = get_next_line(fd);
		cnt++;
	}
	cnt = 0;
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
	while(line != 8)
	{
		free(row);
		row = get_next_line(fd);
		line++;
	}
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

int check_map_coluns(char **map)
{
	int i;

	i = 0;
	while(map[i])
		i++;
	return (i);
}

char **alloc_map(int colums, int line_lenght)
{
	char **map;
	int i;
	
	map = malloc(sizeof(char *) * colums);
	if(!map)
		return NULL;
	i = 0;
	while(map[i] && map)
	{
		map[i] = malloc(line_lenght);
		i++;
	}
	map[i] = NULL;
	return (map);
}

char *alloc_line(char *line, int big_line)
{
	char *new_line;
	int i;

	i = 0;
	new_line = malloc(big_line);
	new_line[0] = 'z';
	while(line && line[i])
	{
		new_line[i + 1] = line[i];
		i++;
	}
	while(i <= big_line)
	{
		new_line[i + 1] = 'z';
		i++;
	}
	new_line[i] = 'z';
	new_line[i + 1] = '\0';
	return (new_line);
}

char **fill_rff_map(char **map)
{
	char **rff_map;
	int cnt;
	int big_line;
	int i;
	
	cnt = check_map_coluns(map);
	big_line = search_for_big_line(map);
	i = 0;
	rff_map = alloc_map(cnt + 3, big_line);
	while(map[i])
	{
		if(i == 0)
			rff_map[i] = alloc_line(NULL, big_line);
		else
			rff_map[i] = alloc_line(map[i], big_line);
		i++;
	}
	rff_map[i] = alloc_line(NULL, big_line);
	//print_map(rff_map);
	return (rff_map);
}

char **get_textures(char *file)
{
	char *row;
	char **textures;
	int fd;
	int text_counter;

	text_counter = 0;
	textures = malloc((sizeof(char *) * 4) + 1);
	row = get_next_line(-1);
	fd = open(file, O_RDONLY);
	row = get_next_line(fd);
	while(row && text_counter < 4)
	{
		if(strncmp(row,"NO", 2) == 0)
			textures[N] = strdup(row + 3);
		else if(strncmp(row,"EA", 2) == 0)
			textures[E] = strdup(row + 3);
		else if(strncmp(row,"SO", 2) == 0)
			textures[S] = strdup(row + 3);
		else if(strncmp(row,"WE", 2) == 0)
			textures[W] = strdup(row + 3);
		text_counter++;
		free(row);
		row = get_next_line(fd);
	}
	return (textures);
}

static int		conv_ex(int nb)
{
	if (nb >= 10)
		return (nb - 10 + 'a');
	else
		return (nb + '0');
}

char	*itoa_base(int value, int base)
{
	int					i;
	char				*str;
	int				tmp;
	
	i = 0;
	tmp = value;
	while (tmp >= base)
	{
		tmp = tmp / base;
		i++;
	}	
	if (!(str = (char *)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	str[i + 1] = '\0';
	while (i >= 0)
	{
		tmp = value % base;
		str[i] = conv_ex(tmp);
		value /= base;
		i--;
	}
	return (str);
}

int	get_hex_color(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}


//Fazer com que ele leia as linhas do F e C e obter o valor para dentro da struct t_color
//Fazer o split da virgula!!!!! Joao e um Deus do codigo, fuck minishell
//Mudei o atoi do libft para dar return a 666 quando a string enviada e nula
void get_rgb(char *line, t_color *s_color)
{
	char **color;
	
	color = ft_split(line, ',');
	if(!color)
		return ;
	s_color->red = ft_atoi(color[0]);
	s_color->green = ft_atoi(color[1]);
	s_color->blue = ft_atoi(color[2]);
	if(s_color->red > 255 || s_color->green > 255 || s_color->blue > 255)
	{
		//print_error("Some color didnt get a value\n");
		printf("Some color didnt get a correct value\n");
		exit(1);
	}
	s_color->hex_color = get_hex_color(s_color->red,s_color->green, s_color->blue);
}

t_color *get_color(char *file, char *type)
{
	char *row;
	t_color *color;
	int fd;

	color = malloc(sizeof(t_color));
	if(!color)
		return (NULL);
	fd = open(file, O_RDONLY);
	row = get_next_line(-1);
	row = get_next_line(fd);
	while(row)
	{
		if(strncmp(row, type, 1) == 0)
			get_rgb(row + 2, color);
		free(row);
		row = get_next_line(fd);
	}
	free(row);
	return (color);
}


t_cube *init_cube(char *file)
{
	t_cube *cube;

	cube = malloc(sizeof(t_cube));
	if(!cube)
		return (NULL);
	cube->textures = get_textures(file);
	cube->f_color = get_color(file, "F");
	cube->map_height = 1400;
	cube->map_width = 2800;
	printf("Floor Colors\nRed: %d Green: %d Blue: %d\n", cube->f_color->red, cube->f_color->green, cube->f_color->blue);
	cube->c_color = get_color(file, "C");
	printf("Ceiling Colors\nRed: %d Green: %d Blue: %d\n", cube->c_color->red, cube->c_color->green, cube->c_color->blue);
	cube->mlx = mlx_init();
	cube->map = fill_map(file);
	cube->rff_map = fill_rff_map(cube->map);
	cube->win = mlx_new_window(cube->mlx, cube->map_width, cube->map_height, "Cub3D");
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
	line_lenght = cube->map_height;
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
	printf("x = %d\ny = %d\n", n_lines, n_rows - ((n_pixels + x) / 2));
	//Fazer com que enquanto ele nao bata numa parede "1" faca linhas, fazer de pouco a pouco
	draw_lines(cube, n_lines, y);
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
	
	//print_map(cube->map);
	put_square(cube, 1400, cube->map_height-50);
	mlx_hook(cube->win, 17, 0, close_cube, cube);
	mlx_key_hook(cube->win, key_press, cube);
	mlx_loop(cube->mlx);
}