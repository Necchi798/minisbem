/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 13:24:40 by mcipolla          #+#    #+#             */
/*   Updated: 2022/10/04 15:36:06 by mcipolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**cut_echo(char **args)
{
	int		i;
	char	**ret;
	int		c;

	i = 0;
	c = 0;
	while (args[i])
		i++;
	ret = malloc((i +1) * sizeof(char *));
	ret[i] = 0;
	i = -1;
	while (args[++i])
	{
		if (!strcmp(args[i], "echo"))
			break ;
	}
	while (args[++i])
	{
		if (args[i][0] == '>')
			break ;
		ret[c] = strdup(args[i]);
		c++;
	}
	ret[c] = 0;
	return (ret);
}

void	ft_putstr_fd(char *str, int fd)
{
	int		i;

	i = 0;
	while (str[i])
	{
		write(fd, &str[i], 1);
		i++;
	}
}

int	my_echo(char **args, int fd)
{
	int		i;
	int		flag;

	i = 1;
	flag = 0;
	if (args[i])
	{
		while (args[i] && ft_strcmp(args[i], "-n") == 0)
		{
			i++;
			flag = 1;
		}
		while (args[i])
		{
			ft_putstr_fd(args[i], fd);
			i++;
			if (args[i] == NULL)
				break ;
			ft_putstr_fd(" ", fd);
		}
	}
	if (flag == 0)
		ft_putstr_fd("\n", fd);
	return (0);
}
