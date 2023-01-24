/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 20:23:27 by mcipolla          #+#    #+#             */
/*   Updated: 2022/10/12 11:35:43 by mcipolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*unclose_quote(char *buff)
{
	int	i;
	int	quote;

	i = -1;
	if (buff == NULL)
		return (NULL);
	while (buff[++i])
	{
		if (buff[i] == '\'' || buff[i] == '"')
		{
			quote = buff[i];
			i++;
			while (buff[i] && buff[i] != quote)
				i++;
			if (buff[i] == '\0')
			{
				printf("minishell: Error, unclosed quotes: %s\n", buff);
				free(buff);
				return (NULL);
			}
		}
	}
	return (buff);
}

int	my_pwd(char **tmp)
{
	char	path[1000];
	int		i;

	i = 0;
	if (strcmp(tmp[0], "pwd") != 0)
	{
		printf("zsh: command not found: %s\n", tmp[0]);
		return (0);
	}
	getcwd(path, 1000);
	printf("%s\n", path);
	return (0);
}
