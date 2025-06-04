/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vluo <vluo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 17:20:08 by vluo              #+#    #+#             */
/*   Updated: 2024/11/13 16:13:12 by vluo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i ++;
	return (i);
}

// #include <stdlib.h>
// #include <stdio.h>
// int main(void)
// {
// 	char *d = malloc(3 * sizeof(char));
// 	d[0] = '4';
// 	d[1] = '2';
// 	d[2] = '\0';
// 	printf("%zu", ft_strlen(d));
// }