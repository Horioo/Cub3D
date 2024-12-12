/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajorge-p <ajorge-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 11:07:24 by ajorge-p          #+#    #+#             */
/*   Updated: 2024/12/12 12:55:16 by ajorge-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

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
			rff_map[i] = alloc_line(map[i - 1], big_line);
		i++;
	}
	rff_map[i] = alloc_line(map[i - 1], big_line);
	rff_map[i + 1] = alloc_line(NULL, big_line);
	//print_map(rff_map);
	return (rff_map);
}
