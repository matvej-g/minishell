/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merdal <merdal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 14:04:37 by merdal            #+#    #+#             */
/*   Updated: 2023/11/10 21:01:31 by merdal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*byte_src;
	unsigned char	*byte_dest;
	size_t			i;

	if (dest == NULL && src == NULL)
		return (NULL);
	byte_src = (unsigned char *)src;
	byte_dest = (unsigned char *)dest;
	i = 0;
	while (i < n)
	{
		byte_dest[i] = byte_src[i];
		i++;
	}
	return (dest);
}
