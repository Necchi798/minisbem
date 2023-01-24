/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 15:15:07 by mcipolla          #+#    #+#             */
/*   Updated: 2022/10/12 16:03:59 by mcipolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*check_empty_pipes(char *buff)
{
	int		i;
	char	*tmp;

	if (buff == NULL)
		return (NULL);
	i = -1;
	while (buff[++i])
	{
		if (buff[i] == '|' )
		{
			if (buff[i + 1] == '&')
			{
				printf("syntax error: near unexpected token `&'\n");
				free(buff);
				return (NULL);
			}
			if (check_emptyline(buff + i) != 0)
				return (buff);
			tmp = readline("> ");
			buff = ft_strjoin(buff, " ");
			buff = ft_strjoin(buff, tmp);
		}
	}
	return (buff);
}

char	**get_path(void)
{
	char	*path;
	char	**ret;
	int		i;

	i = -1;
	path = getenv("PATH");
	if (path == NULL)
	{
		return (NULL);
	}
	else
	{
		ret = ft_split(path, ':');
		while (ret[++i])
			ret[i] = ft_strjoin(ret[i], "/");
	}
	return (ret);
}

void	init(void)
{
	signal(SIGINT, action);
	signal(SIGQUIT, SIG_IGN);
}
