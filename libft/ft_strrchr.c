/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merdal <merdal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 13:39:22 by merdal            #+#    #+#             */
/*   Updated: 2023/11/10 19:21:13 by merdal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	int		i;
	char	s;

	i = ft_strlen(str);
	s = (char)c;
	while (i >= 0)
	{
		if (str[i] == s)
			return ((char *)(&str[i]));
		i--;
	}
	return (NULL);
}
