/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 17:35:44 by mcipolla          #+#    #+#             */
/*   Updated: 2022/10/02 20:49:11 by mcipolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strdup(const char *s1)
{
	int		i;
	char	*tab;

	i = 0;
	while (s1[i])
		i++;
	tab = (char *)malloc(sizeof(char) * i + 1);
	if (!tab)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		tab[i] = s1[i];
		i++;
	}
	tab[i] = '\0';
	return (tab);
}

char	*ft_malloc_strcpy(const char *s, int n)
{
	char	*dst;
	int		i;

	i = 0;
	dst = malloc((n + 1) * sizeof(char));
	if (!dst)
		return (0);
	while (i < n && s[i])
	{
		dst[i] = s[i];
		i++;
	}
	dst[i] = 0;
	return (dst);
}
