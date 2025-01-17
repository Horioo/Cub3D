/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajorge-p <ajorge-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 11:05:26 by ajorge-p          #+#    #+#             */
/*   Updated: 2025/01/16 13:14:59 by ajorge-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] && s2[i])
		i++;
	return (s1[i] - s2[i]);
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