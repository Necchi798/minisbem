/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 19:28:12 by mcipolla          #+#    #+#             */
/*   Updated: 2022/10/07 16:49:34 by mcipolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	my_unset(char **str, char **envp)
{
	int			i;
	int			c;
	char		*swap;

	c = 0;
	while (str[++c])
	{
		i = -1;
		while (envp[++i])
		{
			if (!ft_strncmp(str[c], envp[i], ft_strlen(str[c])) && (envp[i]
					[ft_strlen(str[c])] == '=' || !envp[i][ft_strlen(str[c])]))
			{
				swap = envp[i];
				while (envp[i + 1] != NULL)
				{
					envp[i] = envp[i + 1];
					i++;
				}
				envp[i] = swap;
				envp[i][0] = '\0';
			}
		}
	}
	return (0);
}

int	check_env_path(char *str, char **environ)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
		{
			while (*environ)
			{
				if (ft_strncmp(*environ, str, i) == 0)
					return (0);
				environ++;
			}
			break ;
		}
		i++;
	}
	return (-1);
}

char	**sort_env(char **env)
{
	char	*tmp;
	int		i;

	tmp = NULL;
	i = 0;
	while (env[i + 1])
	{
		if (env[i] && ft_strcmp(env[i], env[i + 1]) > 0)
		{
			tmp = env[i];
			env[i] = env[i + 1];
			env[i + 1] = tmp;
			i = -1;
		}
		i++;
	}
	return (env);
}
