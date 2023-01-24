/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirUtils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 19:28:12 by mcipolla          #+#    #+#             */
/*   Updated: 2022/10/07 12:51:53 by mcipolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_find_new_size(char	*str)
{
	int		i;
	int		size;

	i = -1;
	size = 0;
	while (str[++i])
	{
		if ((str[i] == '>' || str[i] == '<') && str[i + 1]
			!= ' ' && str[i + 1] != '>' && str[i + 1] != '<')
			size++;
		else if (ft_strncmp(str + i, ">>", 2)
			== 0 || ft_strncmp(str + i, "<<", 2) == 0)
		{
			if (str[i + 2] != ' ')
				size++;
		}
	}
	return (i + size);
}

int	ft_addspaces_aux(char *str, int *i, int *c, char *ret)
{
	if (str[*i + 2] == '<' || str[*i + 2] == '>')
	{
		free(ret);
		free(str);
		return (1);
	}
	else if (str[*i + 2] != ' ')
	{
		ret[++*c] = str[++*i];
		ret[++*c] = ' ';
	}
	return (0);
}

char	*ft_addspaces(char *str)
{
	int		i;
	int		c;
	char	*ret;

	i = -1;
	c = 0;
	if (str == NULL)
		return (NULL);
	ret = malloc(sizeof(char) * ft_find_new_size(str) + 1);
	while (str[++i])
	{
		ret[c] = str[i];
		if ((str[i] == '>' || str[i] == '<') && str[i + 1]
			!= ' ' && str[i + 1] != '>' && str[i + 1] != '<')
			ret[++c] = ' ';
		else if (!ft_strncmp(str + i, ">>", 2) || !ft_strncmp(str + i, "<<", 2))
		{
			if (ft_addspaces_aux(str, &i, &c, ret))
				printf("syntax error near unexpected token '%c'\n", str[i + 2]);
		}
		c++;
	}
	ret[c] = '\0';
	free(str);
	return (ret);
}

char	**cut_red(char **args)
{
	int		i;
	int		n;
	char	**ret;

	i = -1;
	n = 0;
	while (args[++i])
		if (!strcmp(args[i], ">>") || args[i][0] == '>'
			|| args[i][0] == '<' || !strcmp(args[i], "<<"))
			n += 2;
	ret = malloc(sizeof(char *) * i - (n) + 1);
	i = 0;
	n = 0;
	while (args[i])
	{
		if (strcmp(args[i], ">>") == 0 || args[i][0]
			== '>' || args[i][0] == '<' || strcmp(args[i], "<<") == 0)
			i += 2;
		else
			ret[n++] = ft_strdup(args[i++]);
	}
	ret[n] = NULL;
	my_free(args);
	return (ret);
}
