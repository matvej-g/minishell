/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgering <mgering@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 13:25:39 by merdal            #+#    #+#             */
/*   Updated: 2024/09/27 14:23:59 by mgering          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t n)
{
	size_t	i;
	size_t	x;

	i = 0;
	if (needle == NULL || needle[i] == '\0')
		return ((char *)(haystack));
	while (i < n && haystack[i] != '\0')
	{
		x = 0;
		while (haystack[i + x] == needle[x] && needle[x] != '\0' && i + x < n)
			x++;
		if (needle[x] == '\0')
			return ((char *)(&haystack[i]));
		i++;
	}
	return (NULL);
}
// #include <stdio.h>

// int main()
// {
// 	char *h = "Hello World";
// 	char *n = "Wor";
// 	size_t size = 20;

// 	char *res = ft_strnstr(h, n, size);

// 	printf("found needle at position: %s\n", res);

// 	return 0;
// }