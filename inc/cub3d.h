/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajorge-p <ajorge-p@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 10:37:26 by ajorge-p          #+#    #+#             */
/*   Updated: 2025/01/18 21:53:02 by ajorge-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# define PI 3.14159265

# include <stdio.h>
# include <sys/wait.h>
# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
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
# define TILE_SIZE 64
# define FOV 66
# define ROTATION_SPEED 3
# define PLAYER_SPEED 15

// For Textures Array
# define N 0
# define E 1
# define S 2
# define W 3
//Screen Settings
# define SCREEN_W 1000
# define SCREEN_H 800


/*
	Mapa e muitooooo diferente do mapa do so_long, tens menos regras para fazer mas pode ser mais dificil de o compreender, o mapa pode ter espacos e depois nos e que decidimos como lidamos com eles
	so pode ter 6 tipos de char [0,1,N,S,W,A] - o NSWA e basicamente a posicao do player e para que direcao esta virado
	O Mapa nao precisa de ser quadrado
	Este gajo tem uma pagina fixe para ver https://hackmd.io/@nszl/H1LXByIE2

	Fazer copia - +2 linhas (uma no inicio e outra no final), cada linha + 2 tamanho
	E depois fazer o reverse_flood_fill de forma a que ele va de fora para dentro e se conseguir entrar entao da erro
*/

typedef struct s_color
{
	int red;
	int green;
	int blue;
	int	hex_color; //Color in Hexadecimal
}				t_color;

typedef struct s_player
{
	int		p_x; //Posicao Jogador X em Pixeis
	int 	p_y; //Posicao Jogador Y em Pixeis
	double 	angle; //Angulo do Player
	float 	fov_rd; //Field of View do Player em Radianos
	double 	dir_x; //Direcao do jogador no eixo do x
	double 	dir_y; //Direcao do jogador no eixo do y
	double 	plane_x; //No Clue
	double 	plane_y; //No Clue
	char	start_dir; //direcao inicial do player
	double	movespeed; //Velocidade do Player
	double	rotation_speed; // Velocidade de Rotacao do player
	bool	m_forward;
	bool	m_backward;
	bool	m_left;
	bool	m_right;
	bool	is_moving;
	
} t_player;

typedef struct s_ray
{
	//Representa a posicao do raio no eixo do x da camera
	double 	camera_x; 
	
	//Representa a direcao do raio
	double 	ray_dir_x; 
	double 	ray_dir_y; 
	
	//Usado para calculos no DDA
	int		map_x;
	int		map_y; 

	// Distancia que o raio tem de percorrer ate encontrar a proxima linha da grid
	double 	delta_dist_x; 
	double 	delta_dist_y; 
	
	//Determina em que direcao vai andar o Raio
	int 	step_x; 
	int		step_y;
	
	//Valor inicial que o raio tem de percorrer ate encontrar a proxima linha, vai ser depois atualizado com o delta_dist ao decorrer do codigo
	double	side_dist_x; 
	double	side_dist_y; 
	
	//Flag para saber se acertou na parede (0 se acertou no eixo do X & 1 se acertou no eixo do Y)
	int		side;

	// Calculos para a altura da Parede
	double	wall_dist;
	int		wall_height;
	
	//Posicao X onde o raio bate na parede
	double	wall_x;
	
	//Coordenada X da textura que sera baseado no valor do wall_x
	int		text_x;

	// Posicoes de inicio e fim para comecar a desenhar
	int		start_pos_draw;
	int		end_pos_draw;
	
} t_ray;

typedef struct s_data
{
	char			**map;
	char			**rff_map;
	int				player_x; // Posicao X do jogador no mapa
	int				player_y; // Posicao Y do jogador no mapa
	int				map_W; // Largura do Mapa
	int				map_H; // Altura do Mapa
	t_color			*f_color;
	t_color			*c_color;
	char			**textures;
	int				**texture_buffer;
	int				**pixel_map;
	
} t_data;

typedef struct s_img
{
	char	*path;
	void	*img;
	int		*addr;
	int		bytes_per_pixel;
	int		line_len;
	int		endian;
	int		width;
	int		height;
} t_img;

typedef struct s_cube
{
	void			*mlx;
	void			*win;
	t_ray			*ray;
	t_data			*data;
	t_player		*player;
	
}t_cube;

//Color
t_color *get_color(char *file, char *type);
void 	get_rgb(char *line, t_color *s_color);

//Draw
void 	draw_lines(t_cube *cube, int x, int y);
void 	put_square(t_cube *cube, int x, int y);
void 	draw_floor(t_cube *cube);
void 	draw_ceiling(t_cube *cube);

//Draw Utils
double 	degrees_to_radians(double degrees);

//Keys
int 	key_press(int keycode, t_cube *cube);
int 	key_release(int keycode, t_cube *cube);

//Map Utils
int 	search_for_big_line(char **map);
int 	check_map_coluns(char **map);
void 	print_map(char **map);
void	map_check(t_cube *cube, int x, int y);
void	get_player_position(t_data *data);

//Map
char 	**fill_rff_map(char **map);
char 	*alloc_line(char *line, int big_line);
char 	**alloc_map(int colums, int line_lenght);
char	**fill_map(char *file);
int		colum_maps(char *file);

//RFF
void 	rff_check(t_data *data, int x, int y);

//Textures
char 	**get_textures(char *file);
void	load_textures(t_cube *cube, t_data *data);

//Utils
int		close_cube(t_cube *cube);
void	check_errors(int ac, char **av);
void	print_error(char *str);
int		checkcub(char *file);
int		ft_strcmp(char *s1, char *s2);

//More Utils
void	*safe_calloc(size_t type, size_t bytes);

//Raycasting
void Raycaster(t_cube *cube);
void create_pixel_map(t_data *data);

//Render
void	draw_pixel_map(t_cube *cube, t_data *data);

//Player
void	move_forward(t_data *data, t_player *p);
void	move_backward(t_data *data, t_player *p);
void	move_right(t_player *p);
void	move_left(t_player *p);
void	move_player(t_data *data, t_player *p);

#endif
