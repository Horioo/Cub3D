/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajorge-p <ajorge-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 17:27:29 by ajorge-p          #+#    #+#             */
/*   Updated: 2023/11/10 16:14:49 by ajorge-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_next_line(int fd)
{
	static char	buffer[FOPEN_MAX][BUFFER_SIZE + 1];
	char		*line;
	int			i;

	i = 0;
	line = NULL;
	if (FOPEN_MAX <= fd || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		if (fd > 0 && FOPEN_MAX > fd)
			while (buffer[fd][i])
				buffer[fd][i++] = '\0';
		return (NULL);
	}
	while (buffer[fd][0] || read(fd, buffer[fd], BUFFER_SIZE) > 0)
	{
		line = ft_join(line, buffer[fd]);
		clear_buffer(buffer[fd]);
		if (line[ft_strlen(line) - 1] == '\n')
			return (line);
	}
	return (line);
}
