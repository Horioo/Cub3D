/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajorge-p <ajorge-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 14:20:19 by ajorge-p          #+#    #+#             */
/*   Updated: 2024/02/19 16:49:34 by ajorge-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_cntwords(char const *s, char lim)
{
	int				counter;
	unsigned int	i;

	counter = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] == lim)
			i++;
		if (s[i] != '\0')
			counter++;
		while (s[i] && s[i] != lim)
			i++;
	}
	return (counter);
}

static char	*ft_strncpy(char *dest, const char *src, size_t n)
{
	size_t	i;

	i = 0;
	while (src[i] && i < n)
	{
		dest[i] = src[i];
		i++;
	}
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}

static char	*ft_strndup(const char *s, size_t n)
{
	char	*str;

	str = malloc(sizeof(char) * (n + 1));
	if (!str)
		return (NULL);
	str = ft_strncpy(str, s, n);
	str[n] = '\0';
	return (str);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		j;
	int		k;
	char	**tabela;

	i = 0;
	k = 0;
	tabela = (char **)malloc(sizeof(char *) * (ft_cntwords(s, c) + 1));
	if (tabela == NULL)
		return (NULL);
	while (s[i])
	{
		while (s[i] == c)
			i++;
		j = i;
		while (s[i] && s[i] != c)
			i++;
		if (i > j)
		{
			tabela[k] = ft_strndup(s + j, i - j);
			k++;
		}
	}
	tabela[k] = NULL;
	return (tabela);
}
