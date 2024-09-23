/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merdal <merdal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 15:35:29 by merdal            #+#    #+#             */
/*   Updated: 2023/11/10 21:01:56 by merdal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	len_d;
	size_t	i;

	len_d = 0;
	i = 0;
	len_d = ft_strlen(dest);
	if (size == 0 || len_d > size)
		return (size + ft_strlen(src));
	while (src[i] != '\0' && len_d + 1 < size)
	{
		dest[len_d] = src[i];
		len_d++;
		i++;
	}
	dest[len_d] = '\0';
	return (ft_strlen(dest) + ft_strlen(src + i));
}
