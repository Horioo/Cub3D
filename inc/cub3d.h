/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajorge-p <ajorge-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 10:37:26 by ajorge-p          #+#    #+#             */
/*   Updated: 2024/12/10 12:31:36 by ajorge-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# define PI 3.14159265

# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include <GL/gl.h>
# include "../libft/libft.h"
# include "../gnl/get_next_line.h"
# include "../minilibx-linux/mlx.h"

# define ESC 65307
# define LEFT 97
# define UP 119
# define RIGHT 100
# define DOWN 115
// For Textures Array
# define N 0
# define E 1
# define S 2
# define W 3
//Screen Settings
# define map_W 1980
# define map_H 1024


/*
	Mapa e muitooooo diferente do mapa do so_long, tens menos regras para fazer mas pode ser mais dificil de o compreender, o mapa pode ter espacos e depois nos e que decidimos como lidamos com eles
	so pode ter 6 tipos de char [0,1,N,S,W,A] - o NSWA e basicamente a posicao do player e para que direcao esta virado
	O Mapa nao precisa de ser quadrado
	Este gajo tem uma pagina fixe para ver https://hackmd.io/@nszl/H1LXByIE2

	Fazer copia - +2 linhas (uma no inicio e outra no final), cada linha + 2 tamanho
	E depois fazer o reverse_flood_fill(ideia do joao) de forma a que ele va de fora para dentro e se conseguir entrar entao da erro
*/

typedef struct s_color
{
	int red;
	int green;
	int blue;
	int	hex_color; //Color in Hexadecimal
}				t_color;

typedef struct s_cube
{
	void			*mlx;
	void			*win;

	char			**map;
	char			**rff_map;
	char			**textures;

	int				player_x;
	int				player_y;
	
	// O valor vai ser nesta estrutura - 255,255,255
	t_color			*f_color; // Floor Color
	t_color			*c_color; // Ceiling Color
	
}			t_cube;


//Color
t_color *get_color(char *file, char *type);
void get_rgb(char *line, t_color *s_color);

//Draw
void draw_lines(t_cube *cube, int x, int y);
void put_square(t_cube *cube, int x, int y);

//Keys
int key_press(int keycode, t_cube *cube);

//Map Utils
int search_for_big_line(char **map);
int check_map_coluns(char **map);
void print_map(char **map);
void	map_check(t_cube *cube, int x, int y);
void	get_player_position(t_cube *cube);

//Map
char **fill_rff_map(char **map);
char *alloc_line(char *line, int big_line);
char **alloc_map(int colums, int line_lenght);
char	**fill_map(char *file);
int	colum_maps(char *file);

//Textures
char **get_textures(char *file);

//Utils
int	close_cube(t_cube *cube);
void	check_errors(int ac, char **av);
void	print_error(char *str);
int	checkcub(char *file);
int	ft_strcmp(char *s1, char *s2);

#endif
