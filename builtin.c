/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 15:30:43 by mcipolla          #+#    #+#             */
/*   Updated: 2022/10/07 09:33:43 by mcipolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_atoi(char *str)
{
	int	neg;
	int	num;
	int	i;

	i = 0;
	neg = 1;
	num = 0;
	while (str[i] <= ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			neg *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = num * 10 + (str[i] - 48);
		i++;
	}
	return (num * neg);
}

void	my_exit(char **cmd)
{
	int	i;

	i = -1;
	if (cmd[1])
	{
		while (cmd[1][++i])
		{
			if (!(cmd[1][i] >= '0' && cmd[1][i] <= '9'))
			{
				printf("exit\n exit: %s: numeric argument required", cmd[1]);
				my_free(cmd);
				exit(255);
			}
		}
		printf("exit\n");
		i = ft_atoi(cmd[1]);
		my_free(cmd);
		while (i < 0 || i > 255)
			i -= 256;
		exit(i);
	}
	my_free(cmd);
	printf("exit\n");
	exit (0);
}

void	exec_builtin(char **cmd, char **envp, int fd)
{
	if (strcmp(cmd[0], "cd") == 0)
		g_exit = my_cd(cmd);
	else if (strcmp(cmd[0], "export") == 0)
		g_exit = my_exp(cmd, envp, 0);
	else if (strcmp(cmd[0], "unset") == 0)
		g_exit = my_unset(cmd, envp);
	else if (strcmp(cmd[0], "echo") == 0)
		g_exit = my_echo(cmd, fd);
	else if (strcmp(cmd[0], "pwd") == 0)
		g_exit = my_pwd(cmd);
	else if (strcmp(cmd[0], "env") == 0)
		g_exit = my_env(cmd, envp);
	else if (strcmp(cmd[0], "exit") == 0)
		my_exit(cmd);
	else
		printf("%s: command not found\n", cmd[0]);
	my_free(cmd);
}

int	check_builtin(char *str)
{
	if (strcmp(str, "export") == 0
		|| strcmp(str, "cd") == 0
		|| strcmp(str, "unset") == 0
		|| strcmp(str, "echo") == 0
		|| strcmp(str, "env") == 0
		|| strcmp(str, "pwd") == 0
		|| strcmp(str, "exit") == 0)
		return (0);
	return (1);
}
