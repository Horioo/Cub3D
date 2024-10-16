/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajorge-p <ajorge-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 16:29:34 by ajorge-p          #+#    #+#             */
/*   Updated: 2024/02/19 16:50:17 by ajorge-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sbstr;
	size_t	i;

	if (start >= (unsigned int)ft_strlen(s))
		len = 0;
	else if (start + (unsigned int)len >= (unsigned int)ft_strlen(s))
		len = ft_strlen(s) - start;
	sbstr = (char *)malloc(len + 1);
	if (sbstr == NULL)
		return (NULL);
	i = 0;
	while (i < len && len != 0)
	{
		sbstr[i] = s[start + i];
		i++;
	}
	sbstr[i] = '\0';
	return (sbstr);
}
