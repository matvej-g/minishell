/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merdal <merdal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 11:59:51 by merdal            #+#    #+#             */
/*   Updated: 2023/11/11 11:23:14 by merdal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	char		*dup;
	size_t		size;

	size = ft_strlen(str) + 1;
	dup = malloc(size);
	if (dup == NULL)
		return (NULL);
	ft_strlcpy(dup, str, size);
	dup[ft_strlen(str)] = '\0';
	return (dup);
}
// #include <stdio.h>

// int main()
// {
// 	char	string[] = "Hello World";

// 	char	*res = ft_strdup(string);

// 	printf("Duplicated str: %s\n", res);

// 	return 0;
// }