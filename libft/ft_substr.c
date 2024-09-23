/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merdal <merdal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 10:46:46 by merdal            #+#    #+#             */
/*   Updated: 2023/11/11 11:27:01 by merdal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;

	if (s == NULL)
		return (NULL);
	if (ft_strlen(s) < start)
	{
		sub = malloc(1);
		if (!sub)
			return (NULL);
		sub[0] = '\0';
		return (sub);
	}
	if (len > ft_strlen(s + start))
		len = ft_strlen(s + start);
	sub = malloc(sizeof(char) * (len + 1));
	if (!sub)
		return (NULL);
	ft_strlcpy(sub, s + start, len + 1);
	sub[ft_strlen(sub)] = '\0';
	return (sub);
}
// #include <stdio.h>

// int main()
// {
// 	char *s = "Hello World";
// 	int	start = 6;
// 	size_t size = 5;

// 	char *res = ft_substr(s, start, size);

// 	printf("new substr: %s\n", res);

// 	return 0;
// }