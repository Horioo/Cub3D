/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajorge-p <ajorge-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 11:12:03 by ajorge-p          #+#    #+#             */
/*   Updated: 2024/12/10 11:56:14 by ajorge-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

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
