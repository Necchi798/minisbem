/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 10:28:05 by mcipolla          #+#    #+#             */
/*   Updated: 2022/09/28 19:47:04 by mcipolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env(char *str)
{
	int		i;
	char	*ret;

	i = 0;
	while (str[i] != '\0' && str[i] != ' ' && str[i] != '\n'
		&& str[i] != '"' && str[i] != '$' && str[i] != '\'')
		i++;
	ret = malloc(sizeof(char) * i + 1);
	i = 0;
	while (str[i] != ' ' && str[i] != '\0' && str[i] != '\n'
		&& str[i] != '"' && str[i] != '$' && str[i] != '\'')
	{
		ret[i] = str[i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}

int	manage_dollar(char *str, char **ret)
{
	char	*aux;
	int		i;

	i = 0;
	if (str[++i] == '?')
	{
		aux = ft_itoa(g_exit);
		*ret = ft_strjoin(*ret, aux);
		free(aux);
		i++;
	}
	else
	{
		aux = get_env(&str[i]);
		if (getenv(aux))
			*ret = ft_strjoin(*ret, getenv(aux));
		free(aux);
		while (str[i] && str[i] != ' ' && str[i] != '"'
			&& str[i] != '$' && str[i] != '\'' && str[i] != '\n')
			i++;
	}
	return (i);
}

int	manage_dq(char *str, char **ret, int i)
{
	int		c;

	c = 0;
	while (str[i] != '"')
	{
		if (str[i] == '$' && str[i + 1] != ' '
			&& str[i + 1] && str[i + 1] != '"')
			i += manage_dollar(&str[i], ret);
		else if (str[i])
			add_char(ret, str[i++]);
	}
	return (i + 1);
}

int	manage_sq(char *first, char **toret)
{
	char	*next;
	char	*aux;

	next = ft_strstr(first, "'");
	if (*(first) == '\'')
		return (2);
	aux = ft_malloc_strcpy(first, next - first);
	*toret = ft_strjoin(*toret, aux);
	free(aux);
	return (next - first + 2);
}

char	*resolve_env(char *str)
{
	char	*ret;

	ret = NULL;
	while (*str && str)
	{
		if (*str == '\'')
			str += manage_sq(str + 1, &ret);
		else if (*str == '"')
			str += manage_dq(str, &ret, 1);
		else if (*str == '$' && *(str + 1) != ' ' && *(str + 1))
			str += manage_dollar(str, &ret);
		else
			add_char(&ret, *(str++));
	}
	return (ret);
}
