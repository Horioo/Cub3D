/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DDA.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajorge-p <ajorge-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 11:28:34 by ajorge-p          #+#    #+#             */
/*   Updated: 2025/01/06 17:48:47 by ajorge-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int abs(int n)
{
	if(n > 0)
		return (n);
	else
		return (n * (-1));
}

void DDA(t_cube *cube, int X0, int Y0, int X1, int Y1) 
{ 
    // calculate dx & dy 
    int dx = X1 - X0; 
    int dy = Y1 - Y0; 
  
    // calculate steps required for generating pixels 
    int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy); 
  
    // calculate increment in x & y for each steps 
    float Xinc = dx / (float)steps; 
    float Yinc = dy / (float)steps; 
  
    // Put pixel for each step 
    float X = X0; 
    float Y = Y0;
	int i = 0;  
    while (i <= steps) { 
        mlx_pixel_put(cube->mlx, cube->win, round(X), round(Y), 
                 0x00FF00FF); // put pixel at (X,Y) 
        X += Xinc; // increment in x at each step 
        Y += Yinc; // increment in y at each step
		i++;
    } 
} 