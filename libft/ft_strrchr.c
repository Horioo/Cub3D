/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajorge-p <ajorge-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 13:33:26 by ajorge-p          #+#    #+#             */
/*   Updated: 2024/02/19 16:50:06 by ajorge-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	i;
	char	*pos;
	char	*s_change;

	i = 0;
	pos = NULL;
	s_change = (char *)s;
	while ((int)i <= ft_strlen(s))
	{
		if (s_change[i] == (char)c)
			pos = &s_change[i];
		i++;
	}
	return (pos);
}
