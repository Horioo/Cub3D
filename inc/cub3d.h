/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajorge-p <ajorge-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 10:37:26 by ajorge-p          #+#    #+#             */
/*   Updated: 2024/10/16 11:34:45 by ajorge-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <GL/gl.h>
# include "../libft/libft.h"
# include "../gnl/get_next_line.h"
# include "../minilibx-linux/mlx.h"



typedef struct s_cube
{
	void			*mlx;
	void			*win;
	// Mapa e muitooooo diferente do mapa do so_long, tens menos regras para fazer mas pode ser mais dificil de o compreender, o mapa pode ter espacos e depois nos e que decidimos como lidamos com eles
	// so pode ter 6 tipos de char [0,1,N,S,W,A] - o NSWA e basicamente a posicao do player e para que direcao esta virado
	// O Mapa nao precisa de ser quadrado
	// Este gajo tem uma pagina fixe para ver https://hackmd.io/@nszl/H1LXByIE2
	char			**map;
	
	int				map_width;
	int				map_height;
	
	// O valor vai ser nesta estrutura - 255,255,255
	char 			*f_color; // Floor Color
	char			*c_color; // Ceiling Color
	
	// Podemos colocar estas texturas num array de chars ou de voids, vai depender no futuro, e fazer com que e.g - [0] = NO; [1] = SO, etc...
	char			*NO_text; // North Texture
	char			*SO_text; // South Texture
	char			*WE_text; // West Texture
	char			*EA_text; // East Texture
	
}			t_cube;

#endif
