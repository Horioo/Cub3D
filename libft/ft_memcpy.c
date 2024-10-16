/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajorge-p <ajorge-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 22:27:44 by marvin            #+#    #+#             */
/*   Updated: 2023/10/20 14:10:38 by ajorge-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*udest;
	unsigned char	*usrc;

	i = 0;
	udest = (unsigned char *)dest;
	usrc = (unsigned char *)src;
	while (i < n && (usrc || udest))
	{
		udest[i] = usrc[i];
		i++;
	}
	return (udest);
}
