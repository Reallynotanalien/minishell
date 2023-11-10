/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edufour <edufour@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 16:12:46 by kafortin          #+#    #+#             */
/*   Updated: 2023/10/24 16:15:23 by edufour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*Duplicates string "src" in a new allocated string, and returns a pointer to 
it.*/
char	*ft_strdup(char *src)
{
	int		len;
	char	*copy;

	if (!src)
		return (NULL);
	len = ft_strlen(src);
	copy = ft_calloc(sizeof(char), len + 1);
	if (copy == NULL)
		return (NULL);
	ft_memmove(copy, src, len);
	return (copy);
}
