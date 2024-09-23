/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merdal <merdal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 11:47:02 by merdal            #+#    #+#             */
/*   Updated: 2024/01/08 11:10:11 by merdal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*join;
	size_t	s1_len;
	size_t	s2_len;

	s1_len = ft_strlen(s1) + 1;
	s2_len = ft_strlen(s2);
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	join = (char *)malloc((s1_len + s2_len) * sizeof(char));
	if (join == NULL)
		return (NULL);
	ft_strlcpy(join, s1, s1_len);
	ft_strlcat(join, s2, s1_len + s2_len);
	join[ft_strlen(join)] = '\0';
	return (join);
}
// #include <stdio.h>

// int main()
// {
// 	char *s1 = "Hello ";
// 	char *s2 = "World";

// 	char *res = ft_strjoin(s1, s2);

// 	printf("joined String: %s\n", res);

// 	return 0;
// }