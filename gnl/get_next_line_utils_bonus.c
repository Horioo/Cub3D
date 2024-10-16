/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajorge-p <ajorge-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 18:05:51 by ajorge-p          #+#    #+#             */
/*   Updated: 2023/11/10 15:47:05 by ajorge-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	ft_strlen(char const *s)
{
	int	len;

	len = 0;
	while (s && s[len] && s[len] != '\n')
		len++;
	if (s && s[len] == '\n')
		len++;
	return (len);
}

char	*ft_join(char *str, char *buffer)
{
	int		i;
	int		j;
	char	*line;

	i = 0;
	j = 0;
	line = malloc(ft_strlen(str) + ft_strlen(buffer) + 1);
	if (!line)
		return (NULL);
	while (str && str[i])
	{
		line[i] = str[i];
		i++;
	}
	while (buffer[j] != '\n' && buffer[j])
	{
		line[i + j] = buffer[j];
		j++;
	}
	if (buffer[j] == '\n')
		line[i + j++] = '\n';
	line[i + j] = '\0';
	if (str)
		free(str);
	return (line);
}

void	clear_buffer(char *buffer)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (buffer[i] != '\n' && i < BUFFER_SIZE)
		buffer[i++] = '\0';
	if (buffer[i] == '\n')
	{
		buffer[i++] = '\0';
		while (i < BUFFER_SIZE)
		{
			buffer[j++] = buffer[i];
			buffer[i] = '\0';
			i++;
		}
	}
}
