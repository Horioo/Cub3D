/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajorge-p <ajorge-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 16:50:27 by ajorge-p          #+#    #+#             */
/*   Updated: 2024/03/14 18:26:53 by ajorge-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_numsize(long int n)
{
	long int	save;
	long int	size;

	size = 1;
	save = n;
	if (save < 0)
	{
		size++;
		save = -save;
	}
	while (save / 10)
	{
		save = save / 10;
		size++;
	}
	return (size);
}

char	*ft_itoa(int n)
{
	char		*str;
	int			size;
	long int	ln;

	ln = n;
	size = ft_numsize(ln);
	str = (char *)malloc(size + 1);
	if (str == NULL)
		return (NULL);
	if (ln < 0)
	{
		str[0] = '-';
		ln = -ln;
	}
	if (ln == 0)
		str[0] = '0';
	str[size] = '\0';
	size--;
	while (size >= 0 && ln > 0)
	{
		str[size--] = '0' + (ln % 10);
		ln = ln / 10;
	}
	return (str);
}
