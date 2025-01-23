/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajorge-p <ajorge-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 22:33:51 by marvin            #+#    #+#             */
/*   Updated: 2023/10/19 17:01:34 by ajorge-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char		*cdest;
	const char	*csrc;

	if (dest == NULL && src == NULL)
		return (NULL);
	cdest = dest;
	csrc = src;
	if (cdest < csrc || cdest >= csrc + n)
	{
		while (n--)
			*cdest++ = *csrc++;
	}
	else
	{
		cdest += n;
		csrc += n;
		while (n--)
			*(--cdest) = *(--csrc);
	}
	return (dest);
}
