/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merdal <merdal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 13:31:09 by merdal            #+#    #+#             */
/*   Updated: 2023/11/10 21:01:41 by merdal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *mem, int value, size_t n)
{
	unsigned char	byte_value;
	unsigned char	*dest;
	size_t			i;

	byte_value = (unsigned char)value;
	dest = (unsigned char *)mem;
	i = 0;
	while (i < n)
	{
		dest[i] = byte_value;
		i++;
	}
	return (mem);
}
