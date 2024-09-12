/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artberna <artberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 13:43:31 by artberna          #+#    #+#             */
/*   Updated: 2024/06/20 10:05:48 by artberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_library.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new_str;
	int		i;
	int		j;
	int		length;

	if (!s1 && !s2)
		return (NULL);
	length = (ft_strlen(s1) + ft_strlen(s2));
	i = 0;
	j = 0;
	new_str = (char *)malloc(sizeof(char) * length + 1);
	if (!new_str)
		return (NULL);
	while (s1[i])
	{
		new_str[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		new_str[i + j] = s2[j];
		j++;
	}
	new_str[i + j] = '\0';
	return (new_str);
}

/*
#include <stdio.h>

int	main(void)
{
	char	*s1;
	char	*s2;
	char	*concat;

	s1 = "Hello";
	s2 = "CHACAL";
	concat = ft_strjoin(s1, s2);
	printf(":%s:\n", concat);
	return (0);
}
*/