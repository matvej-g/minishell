/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merdal <merdal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 14:42:34 by merdal            #+#    #+#             */
/*   Updated: 2023/11/10 20:31:53 by merdal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_count_words(char *s, char c)
{
	int	word;

	word = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
		{
			while (*s && *s != c)
				s++;
			word++;
		}
	}
	return (word);
}

void	*ft_string_split(char **split, char const *s, char c, int total_words)
{
	int			i;
	int			len;
	char const	*start;
	char const	*end;

	i = 0;
	start = s;
	while (i < total_words)
	{
		while (*start == c)
			start++;
		end = ft_strchr(start, c);
		if (end == NULL)
			end = start + ft_strlen(start);
		len = end - start + 1;
		split[i] = (char *)malloc(len + 1);
		if (split[i] == NULL)
			return (NULL);
		ft_strlcpy(split[i], start, len);
		split[i][len] = '\0';
		i++;
		start = end + 1;
	}
	split[total_words] = NULL;
	return (0);
}

char	**ft_split(char const *s, char c)
{
	char	**split;
	int		total_words;

	if (s == NULL)
		return (NULL);
	total_words = ft_count_words((char *)s, c);
	if (total_words == 0)
	{
		split = (char **)malloc(sizeof(char *));
		if (split != NULL)
			split[0] = NULL;
	}
	else
	{
		split = (char **)malloc(sizeof(char *) * (total_words + 1));
		if (split != NULL)
			ft_string_split(split, s, c, total_words);
	}
	return (split);
}
// #include <stdio.h>

// int main() {
//     char input[] = "This is a sample string split by spaces";
//     char delimiter = ' ';

//     // Split the input string into words using ft_split
//     char **result = ft_split(input, delimiter);

//     if (result != NULL) {
//         // Print the individual words
//         for (int i = 0; result[i] != NULL; i++) {
//             printf("Word %d: %s\n", i, result[i]);
//         }

//         // Free the memory allocated for the result
//         for (int i = 0; result[i] != NULL; i++) {
//             free(result[i]);
//         }
//         free(result);
//     } else {
//         printf("Memory allocation failed\n");
//     }

//     return 0;
// }