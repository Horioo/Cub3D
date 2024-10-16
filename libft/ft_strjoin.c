/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajorge-p <ajorge-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 18:03:50 by ajorge-p          #+#    #+#             */
/*   Updated: 2023/10/17 13:05:49 by ajorge-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	int		i;

	if (s1 && s2)
	{
		str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
		if (str)
		{
			i = 0;
			while (*s1)
				str[i++] = *s1++;
			while (*s2)
				str[i++] = *s2++;
			str[i] = '\0';
			return (str);
		}
	}
	return (NULL);
}
