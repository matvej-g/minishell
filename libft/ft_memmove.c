/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merdal <merdal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 15:20:19 by merdal            #+#    #+#             */
/*   Updated: 2023/11/10 21:01:36 by merdal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*byte_dest;
	unsigned char	*byte_src;
	size_t			i;

	byte_dest = (unsigned char *)dest;
	byte_src = (unsigned char *)src;
	if (dest == src || n == 0)
		return (dest);
	if (byte_dest > byte_src && byte_dest < byte_src + n)
	{
		i = n;
		while (i--)
		{
			byte_dest[i] = byte_src[i];
		}
	}
	else
	{
		while (n--)
		{
			*byte_dest++ = *byte_src++;
		}
	}
	return (dest);
}
