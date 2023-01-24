/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 17:25:45 by mcipolla          #+#    #+#             */
/*   Updated: 2022/10/03 15:32:26 by mcipolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strstr(char *str, char *to_find)
{
	int	i;
	int	j;

	i = 0;
	while (str[i] != '\0')
	{
		j = 0;
		while (to_find[j] == str[i + j])
		{
			if (to_find[j + 1] == '\0')
				return (str + i);
			j++;
		}
		i++;
	}
	return (0);
}

int	parse_wild(char *wild_str, char *str, char **splitted)
{
	int		i;
	int		size;

	i = 0;
	size = strlen(wild_str);
	if ((wild_str[0] != '*' && str[0] != wild_str[0]) || (wild_str[size]
			!= '*' && str[strlen(str) - 1] != wild_str[size - 1]))
	{
		my_free(splitted);
		return (0);
	}
	while (*str && splitted[i])
	{
		if (*str == splitted[i][0] && ft_strstr(str, splitted[i]) == str)
			i++;
		str++;
	}
	if (!splitted[i])
	{
		my_free(splitted);
		return (1);
	}
	my_free(splitted);
	return (0);
}

char	*parse_files(char *wild)
{
	DIR				*d;
	struct dirent	*dir;
	char			*ret;

	ret = NULL;
	d = opendir(".");
	if (d)
	{
		dir = readdir(d);
		while (dir != NULL)
		{
			if (parse_wild(wild, dir->d_name, ft_split(wild, '*')) == 1)
			{
				ret = ft_strjoin(ret, dir->d_name);
				ret = ft_strjoin(ret, " ");
			}
			dir = readdir(d);
		}
	}
	closedir(d);
	return (ret);
}

char	**check_wild(char **args, int i)
{
	char	**ret;
	char	*tmp;
	char	*aux;

	i = -1;
	tmp = NULL;
	while (args[++i])
	{
		if (ft_strchr(args[i], '*') != NULL)
		{
			aux = parse_files(args[i]);
			if (aux)
				tmp = ft_strjoin(tmp, aux);
			else
				tmp = ft_strjoin(tmp, args[i]);
			free(aux);
		}
		else
			tmp = ft_strjoin(tmp, args[i]);
		tmp = ft_strjoin(tmp, " ");
	}
	ret = ft_split(tmp, ' ');
	free(tmp);
	my_free(args);
	return (ret);
}
