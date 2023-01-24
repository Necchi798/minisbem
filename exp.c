/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 19:28:12 by mcipolla          #+#    #+#             */
/*   Updated: 2022/10/06 18:57:25 by mcipolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	my_exp(char **tmp, char **envp, int i)
{
	char		**export;
	char		*aux;

	if (tmp[1] != NULL)
		while (tmp[++i] != NULL)
			add_env(tmp[i], &envp[0]);
	if (tmp[1] != NULL)
		return (0);
	export = cpy_matrix(envp, -1);
	export = sort_env(export);
	i = -1;
	while (export[++i])
	{
		if (check_empty_env(export[i]) == -2)
			aux = ft_strjoin(export[i], "''");
		else
		{
			aux = ft_strdup(export[i]);
			free(export[i]);
		}
		printf("%s\n", aux);
		free(aux);
	}
	free(export);
	return (0);
}

int	my_env( char **tmp, char **envp)
{
	int			i;
	int			s;

	if (tmp[1] != NULL)
	{
		if (check_env_path(tmp[1], envp) == -1)
		{
			printf("env: %s: No such file or directory\n", tmp[1]);
			return (1);
		}
	}
	i = -1;
	while (envp[++i])
	{
		s = check_empty_env(envp[i]);
		if (s == -1 || s == -2)
		{
			if (s == -2)
				printf("%s''\n", envp[i]);
			else
				printf("%s\n", envp[i]);
		}
	}
	return (0);
}

int	until_ugual(char *s1, char *s2)
{
	int	i;
	int	c;

	i = 0;
	while (s1[i] && s1[i] != '=')
		i++;
	c = 0;
	while (s2[c] && s2[c] != '=')
		c++;
	if (i == c && ft_strncmp(s1, s2, c) == 0)
		return (0);
	return (1);
}

void	add_env_aux(char **envp, int i, char **arr, char *str)
{
	int	j;

	j = -1;
	while (arr[++j])
	{
		if (envp[i] == arr[j])
		{
			free(envp[i]);
			envp[i] = ft_strdup(str);
			arr[j] = envp[i];
			envp[i + 1] = NULL;
			return ;
		}
	}
	envp[i] = ft_strdup(str);
	arr[j] = envp[i];
	envp[i + 1] = NULL;
}

void	add_env(char *str, char **envp)
{
	int			i;
	int			c;
	static char	*arr[1024];

	i = -1;
	while (envp[++i] && envp[i][0] != '\0')
	{
		if (until_ugual(str, envp[i]) == 0 || ft_strcmp(str, envp[i]) == 0)
		{
			c = 0;
			while (envp[i][c] && envp[i][c] != '=')
				c++;
			if (!ft_strchr(str, '='))
				return ;
			while (str[c])
			{
				envp[i][c] = str[c];
				c++;
			}
			envp[i][c] = '\0';
			return ;
		}
	}
	add_env_aux(envp, i, arr, str);
}
