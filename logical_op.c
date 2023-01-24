/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logical_op.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 14:25:42 by mcipolla          #+#    #+#             */
/*   Updated: 2022/10/12 16:06:02 by mcipolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_emptyline(char *str)
{
	if (*str == '\0')
		return (0);
	while (*str && *str != ' ')
		str++;
	while (*str && *str == ' ')
		str++;
	if (*str == '|' || *str == '&')
		return (1);
	if (*str != '\0')
		return (2);
	return (0);
}

char	*cut_str(char *str, int limiter)
{
	char	*ret;
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\0' || str[i] == ')' || str[i] == '|'
			|| str[i] == '&')
			break ;
		i++;
	}
	if (str[i] == '\0')
		i++;
	limiter = i - 1;
	ret = malloc(sizeof(char) * limiter);
	ret[limiter] = '\0';
	if (str[0] == '(')
		str++;
	i = -1;
	while (++i < limiter)
		ret[i] = str[i];
	return (ret);
}

int	exec_logical(char *buff, char **mypath, int i, char **envp)
{
	char	*tmp;
	char	**args;

	tmp = cut_str(buff, i);
	args = ft_split(tmp, ' ');
	args = check_wild(args, -1);
	check_pipes(tmp, mypath, remove_quotes(args), envp);
	my_free(args);
	free(tmp);
	if (buff[i + 1] == '\0')
		return (1);
	return (0);
}

int	logical_operator(char *buff, char **mypath, char *log, char **envp)
{
	int		i;

	if (*buff == ' ')
		buff++;
	i = 0;
	while (buff[i])
	{
		if ((buff[i + 1] == '\0' && log != NULL)
			|| ft_strncmp(&buff[i], "&&", 2) == 0
			|| ft_strncmp(buff + i, "||", 2) == 0)
		{
			if (log == NULL
				|| (ft_strncmp(log, "&&", 2) == 0 && g_exit == 0)
				|| (ft_strncmp(log, "||", 2) == 0 && g_exit != 0))
				if (exec_logical(buff, mypath, i, envp) == 1)
					return (0);
			logical_operator(buff + i + 2, mypath, buff + i, envp);
			return (0);
		}
		i++;
	}
	return (1);
}

char	*check_empty_logical(char *buff)
{
	int		i;
	char	*tmp;

	if (buff == NULL)
		return (NULL);
	i = -1;
	while (buff[++i])
	{
		if (!ft_strncmp(buff + i, "&&", 2) || !ft_strncmp(buff + i, "||", 2))
		{
			if (buff[i + 2] == '&' || buff[i + 2] == '|')
			{
				printf("syntax error near unexpected token ");
				printf("'%c%c'\n", buff[i + 2], buff[i + 3]);
				return (NULL);
			}
			else if (check_logical(buff + i + 2) == 0)
			{
				tmp = readline("> ");
				buff = ft_strjoin(buff, tmp);
				free(tmp);
			}
		}
	}
	return (buff);
}
