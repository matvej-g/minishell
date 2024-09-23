/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merdal <merdal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 13:27:25 by merdal            #+#    #+#             */
/*   Updated: 2023/11/10 21:01:23 by merdal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_numlen(int n)
{
	int	len;

	len = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		len++;
		n = -n;
	}
	while (n)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*dest;
	int		i;
	int		len;
	long	num;

	num = n;
	len = ft_numlen(n);
	dest = malloc((len + 1) * sizeof(char));
	if (dest == NULL)
		return (NULL);
	i = len -1;
	if (num < 0)
		num = -num;
	while (i >= 0)
	{
		dest[i--] = (num % 10) + '0';
		num /= 10;
	}
	if (n < 0 && dest[0] == '0')
		dest[0] = '-';
	dest[len] = '\0';
	return (dest);
}
