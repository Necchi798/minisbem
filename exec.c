/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 15:36:59 by mcipolla          #+#    #+#             */
/*   Updated: 2022/10/12 15:31:16 by mcipolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**cmd_path(char **args)
{
	int		i;
	char	*tmp;

	if (args[0][0] == '/')
	{
		i = ft_strlen(args[0]);
		while (args[0][i] != '/')
			i--;
		if (args[0][i - 1] == '.')
			i--;
		tmp = ft_strdup(args[0] + i);
		free(args[0]);
		args[0] = tmp;
	}
	return (args);
}

void	my_exec(char **mypath, char **environ, char **cmd)
{
	char	*tmp;
	int		pid;
	int		status;

	pid = fork();
	signal(SIGINT, action_in_process);
	signal(SIGQUIT, action_in_process);
	if (pid == 0)
	{
		if (check_dot(cmd, environ) == -1)
		{
			while (mypath && *mypath)
			{
				tmp = ft_strjoin(*mypath++, cmd[0]);
				if (access(tmp, R_OK) == 0)
					execve(tmp, cmd, environ);
				free(tmp);
			}
			printf("%s: command not found\n", cmd[0]);
		}
		exit(127);
	}
	waitpid(pid, &status, 0);
	set_global(status);
	my_free(cmd);
}

void	set_fd(int *stdin_cpy, int *stdout_cpy, int flag)
{
	if (flag == 0)
	{
		*stdin_cpy = dup(0);
		*stdout_cpy = dup(1);
	}
	else if (flag == 1)
	{
		dup2(*stdin_cpy, 0);
		dup2(*stdout_cpy, 1);
	}
	else if (flag == 2)
	{
		close(*stdin_cpy);
		close(*stdout_cpy);
	}
}

void	split_exec(char **mypath, char **cmd, char **envp)
{
	int	stdout_cpy;
	int	stdin_cpy;
	int	fd;

	cmd = cmd_path(cmd);
	set_fd(&stdin_cpy, &stdout_cpy, 0);
	if (cmd[0] == NULL)
		return ;
	if (between_parentheses(cmd[0]) == 0)
	{
		exec_subshell(cmd, envp);
		return ;
	}
	fd = check_redir(cmd);
	cmd = cut_red(cmd);
	if (cmd[0] == NULL)
		free(cmd);
	else if (check_builtin(cmd[0]) == 0)
		exec_builtin(cmd, envp, fd);
	else
		my_exec(mypath, envp, cmd);
	set_fd(&stdin_cpy, &stdout_cpy, 1);
	set_fd(&stdin_cpy, &stdout_cpy, 2);
}
