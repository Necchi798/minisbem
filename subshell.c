/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 16:27:10 by mcipolla          #+#    #+#             */
/*   Updated: 2022/10/12 14:52:58 by mcipolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*remove_parentheses(char *str)
{
	size_t	i;
	size_t	c;
	char	*ret;
	size_t	size;

	if (str[1] == ' ')
	{
		size = ft_strlen(str) - 3;
		i = 2;
	}
	else
	{
		size = ft_strlen(str) - 2;
		i = 1;
	}
	c = -1;
	ret = malloc(sizeof(char) * size);
	ret[size] = '\0';
	while (++c < size)
	{
		ret[c] = str[i];
		i++;
	}
	free(str);
	return (ret);
}

void	exec_subshell(char **args, char **envp)
{
	char		**cmd;
	int			pid;
	int			status;

	cmd = (char **)malloc(sizeof(char *) * 3);
	cmd[0] = ft_strdup("./minishell");
	cmd[1] = remove_parentheses(args[0]);
	cmd[2] = NULL;
	pid = fork();
	if (pid == 0)
		execve(cmd[0], cmd, envp);
	else
	{
		waitpid(pid, &status, 0);
		my_free(cmd);
		free(args);
		set_global(status);
	}
}
