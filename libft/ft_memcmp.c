/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merdal <merdal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 12:16:58 by merdal            #+#    #+#             */
/*   Updated: 2023/11/10 19:21:49 by merdal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *str1, const void *str2, size_t n)
{
	const unsigned char	*byte_str1;
	const unsigned char	*byte_str2;
	size_t				i;

	byte_str1 = (unsigned char *)str1;
	byte_str2 = (unsigned char *)str2;
	i = 0;
	while (i < n)
	{
		if (byte_str1[i] == byte_str2[i])
		{
			i++;
		}
		else
		{
			return (byte_str1[i] - byte_str2[i]);
		}
	}
	return (0);
}
