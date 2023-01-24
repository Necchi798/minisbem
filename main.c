/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 19:08:41 by mcipolla          #+#    #+#             */
/*   Updated: 2022/10/12 16:05:14 by mcipolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*check_empty(char *buff)
{
	buff = check_empty_logical(check_empty_parentheses(buff));
	if (!(ft_strchr(buff, '(')) && ft_strchr(buff, ')'))
	{
		printf("syntax error: near unexpected token `)'\n");
		buff = NULL;
	}
	buff = check_empty_pipes(buff);
	return (buff);
}

char	*first_check(char *buff)
{
	char	*tmp;

	if (buff == NULL)
		msg_exit();
	if (buff[0] == '\0')
		return (buff);
	tmp = buff;
	buff = check_empty(buff);
	if (buff == NULL)
		add_history(tmp);
	else
		add_history(buff);
	buff = ft_addspaces(buff);
	buff = unclose_quote(buff);
	if (buff == NULL)
	{
		buff = ft_strdup("");
		g_exit = 258;
	}
	return (buff);
}

void	ft_start_parsing_aux(char **args2, int c)
{
	char	*aux;
	char	*aux1;

	aux1 = get_env(args2[c]);
	aux = getenv(aux1);
	free(aux1);
	if (args2[c][0] == '$' && aux && args2[c][1] != ' ')
	{
		free(args2[c]);
		args2[c] = aux;
	}
}

void	start_parsing(char *buff, char **mypath, char **envp)
{
	char	**args;
	char	**args2;
	int		i;
	int		c;

	i = 0;
	args = ft_split(buff, ';');
	while (args[i])
	{
		args2 = ft_split(args[i], ' ');
		c = -1;
		while (args2[++c])
		{
			ft_start_parsing_aux(args2, c);
		}
		args2 = check_wild(args2, -1);
		if (args2 == NULL)
			return ;
		if (logical_operator(args[i], mypath, NULL, envp) == 1)
			check_pipes(args[i], mypath, remove_quotes(args2), envp);
		my_free(args2);
		i++;
	}
	my_free(args);
}

int	main(int argc, char *argv[], char **envp)
{
	char		*buff;
	char		**mypath;
	extern char	**environ;

	clt_echo("-ctlecho");
	while (1)
	{
		init();
		environ = envp;
		mypath = get_path();
		if (argc > 1)
			buff = argv[1];
		else
			buff = first_check(readline("minishell: "));
		if (buff[0] != '\0')
			start_parsing(buff, mypath, envp);
		if (argc > 1)
			exit(g_exit);
		free(buff);
		if (mypath)
			my_free(mypath);
	}
	return (g_exit);
}
