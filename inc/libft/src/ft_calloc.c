/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamini <ahamini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 10:59:29 by ahamini           #+#    #+#             */
/*   Updated: 2025/02/28 10:59:45 by ahamini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"
#include <stdlib.h>

void	ft_bzero(void *ptr, unsigned long len)
{
	unsigned char	*str;

	str = ptr;
	while (len--)
		*str++ = 0;
}

void	*ft_calloc(size_t nbr, size_t size)
{
	void	*result;

	if (nbr == 0 || size == 0 || ((size_t) - 1 / nbr) < size)
		return (malloc(0));
	result = malloc(nbr * size);
	if (!result)
		return (NULL);
	ft_bzero(result, nbr * size);
	return (result);
}
