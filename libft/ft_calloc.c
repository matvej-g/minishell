/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merdal <merdal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 10:45:47 by merdal            #+#    #+#             */
/*   Updated: 2023/11/06 13:06:02 by merdal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t n_items, size_t size)
{
	void	*ptr;

	ptr = malloc(n_items * size);
	if (!ptr)
		return (NULL);
	ft_memset(ptr, 0, n_items * size);
	return (ptr);
}
