/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajorge-p <ajorge-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 12:17:09 by ajorge-p          #+#    #+#             */
/*   Updated: 2024/12/12 12:17:22 by ajorge-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

// Funcao para transformar em radians para depois ser possivel obter os angulos para fazer o cone de visao
double degrees_to_radians(double degrees)
{
	return (degrees * (PI / 180.00));
}
