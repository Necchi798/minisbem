/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 17:51:30 by mcipolla          #+#    #+#             */
/*   Updated: 2022/10/12 16:05:23 by mcipolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**cut_heredoc(char **args)
{
	int		i;
	int		n;
	char	**ret;

	i = -1;
	n = 0;
	while (args[++i])
	{
		if (strcmp(args[i], "<<") == 0)
			n += 2;
	}
	ret = malloc(sizeof(char *) * i - (n) + 1);
	i = 0;
	n = 0;
	while (args[i])
	{
		if (strcmp(args[i], "<<") == 0)
			i += 2;
		else
			ret[n++] = ft_strdup(args[i++]);
	}
	ret[n] = NULL;
	my_free(args);
	return (ret);
}

void	do_pipe(int std_cpy[2], char **cmd, char **envp, char **next)
{
	int		end[2];
	int		pid;
	char	**mypath;

	pipe(end);
	mypath = get_path();
	pid = fork();
	if (pid == 0)
	{
		close(end[0]);
		if (next == NULL)
			dup2(std_cpy[1], STDOUT_FILENO);
		else
			dup2(end[1], STDOUT_FILENO);
		close(end[1]);
		split_exec(mypath, cmd, envp);
		exit(0);
	}
	if (here_doc_pipes(next) == 1)
		dup2(end[0], STDIN_FILENO);
	close(end[1]);
	close(end[0]);
	if (next != NULL)
		my_free(next);
	my_free(mypath);
}

void	pipex(char **pipes, int n_pipes, char **envp)
{
	int		i;
	char	**args;
	int		std_cpy[2];

	i = -1;
	set_fd(&std_cpy[0], &std_cpy[1], 0);
	while (++i <= n_pipes)
	{
		args = ft_split(pipes[i], ' ');
		if (i > 0)
			args = cut_heredoc(args);
		if (i == n_pipes)
			do_pipe(std_cpy, args, envp, NULL);
		else
			do_pipe(std_cpy, args, envp, ft_split(pipes[i + 1], ' '));
		my_free(args);
	}
	i = -1;
	while (++i <= n_pipes)
		waitpid(-1, NULL, 0);
	set_fd(&std_cpy[0], &std_cpy[1], 1);
	set_fd(&std_cpy[0], &std_cpy[1], 2);
}

void	check_pipes(char *str, char **mypath, char **args, char **envp)
{
	char	**pipes;
	int		matrix_size;
	int		n_pipes;

	matrix_size = 0;
	pipes = ft_split(str, '|');
	while (pipes[matrix_size])
		matrix_size++;
	n_pipes = matrix_size - 1;
	if (matrix_size > 1)
	{
		pipex(pipes, n_pipes, envp);
		my_free(args);
	}
	else
		split_exec(mypath, args, envp);
	my_free(pipes);
}
