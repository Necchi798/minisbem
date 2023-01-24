/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 15:33:53 by mcipolla          #+#    #+#             */
/*   Updated: 2022/10/12 16:14:20 by mcipolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	here_doc(char *limiter)
{
	char	*buff;
	char	*ret;
	int		end[2];

	ret = NULL;
	while (1)
	{
		buff = readline("> ");
		if (ft_strcmp(buff, limiter) == 0)
			break ;
		ret = ft_strjoin(ret, buff);
		ret = ft_strjoin(ret, "\n");
		free(buff);
	}
	pipe(end);
	dup2(end[0], 0);
	write (end[1], ret, ft_strlen(ret));
	close(end[1]);
	close(end[0]);
	free(ret);
	free(buff);
}

char	*get_limiter(char **args)
{
	int		i;
	char	*ret;

	i = 0;
	if (args == NULL)
		return (NULL);
	ret = NULL;
	while (args[i])
	{
		if (ft_strcmp(args[i], "<<") == 0)
			ret = args[i + 1];
		i++;
	}
	return (ret);
}

int	write_heredoc(int end[2], char *ret, char *buff)
{
	write (end[1], ret, ft_strlen(ret));
	dup2(end[0], 0);
	close(end[1]);
	free(ret);
	free(buff);
	return (0);
}

int	here_doc_pipes(char **args)
{
	char	*buff;
	char	*ret;
	char	*limiter;
	int		end[2];

	ret = NULL;
	limiter = get_limiter(args);
	if (limiter == NULL)
		return (1);
	pipe(end);
	while (1)
	{
		buff = readline("> ");
		if (ft_strcmp(buff, limiter) == 0)
			break ;
		ret = ft_strjoin(ret, buff);
		ret = ft_strjoin(ret, "\n");
		free(buff);
	}
	if (ret)
		return (write_heredoc(end, ret, buff));
	free(buff);
	return (1);
}
