/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 17:09:04 by mcipolla          #+#    #+#             */
/*   Updated: 2022/07/19 18:37:44 by mcipolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*trunc_str(char *str, char c, int n)
{
	int		i;
	int		x;
	char	*ret;

	i = 0;
	x = 0;
	while (x < n)
	{
		if (str[i] == c)
			x++;
		i++;
	}
	ret = malloc(sizeof(char) * i);
	i = 0;
	x = 0;
	while (x < n)
	{
		ret[i] = str[i];
		if (str[i] == c)
			x++;
		i++;
	}
	ret[i - 1] = '\0';
	return (ret);
}

int	my_cd(char **tmp)
{
	int		i;
	char	path[99999];
	char	*reset_path;

	i = 0;
	while (tmp[i])
		i++;
	if (i == 1)
	{
		getcwd(path, 99999);
		reset_path = trunc_str(path, '/', 3);
		chdir(reset_path);
		return (0);
	}
	if (tmp[1] && chdir(tmp[1]) == -1)
	{
		if (i > 2)
			printf("cd: too many arguments\n");
		else
			printf("cd: no such file or directory: %s\n", tmp[1]);
		return (1);
	}
	return (0);
}
