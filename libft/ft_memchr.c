/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merdal <merdal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 11:45:11 by merdal            #+#    #+#             */
/*   Updated: 2023/11/10 19:21:57 by merdal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *str, int c, size_t n)
{
	unsigned char	*cstr;
	unsigned char	cc;
	size_t			i;

	i = 0;
	cstr = (unsigned char *)str;
	cc = (unsigned char)c;
	while (i < n)
		if (cstr[i++] == cc)
			return (cstr + --i);
	return (NULL);
}
