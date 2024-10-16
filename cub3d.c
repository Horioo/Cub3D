/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajorge-p <ajorge-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 10:13:39 by ajorge-p          #+#    #+#             */
/*   Updated: 2024/10/16 11:22:32 by ajorge-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/cub3d.h"

void	map_check(t_cube *cube, int x, int y)
{
	
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

int	close_game(t_cube *cube)
{
	(void)cube;
	//errormsg(cube, "Bye Bye >:)", 0);
	exit(0); //Remove later and uncomment errormsg()
	return (0);
}

int main(int ac, char **av)
{
	t_cube *cube;
	check_errors(ac, av);
	
	cube = init_cube(av[1]);
	mlx_hook(cube->win, 17, 0, close_game, cube);
	mlx_loop(cube->mlx);

}