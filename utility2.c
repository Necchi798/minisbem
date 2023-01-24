/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 18:32:21 by mcipolla          #+#    #+#             */
/*   Updated: 2022/10/10 14:09:59 by mcipolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	skip_chars(char c)
{
	if (c && c != ' ' && c != '"'
		&& c != '\'' && c != '\n')
		return (0);
	return (1);
}

void	add_char(char **toret, char a)
{
	char	aux[2];

	aux[0] = a;
	aux[1] = 0;
	*toret = ft_strjoin(*toret, aux);
}

void	ft_increase_shlvl(char **environ)
{
	char		*nb;
	int			tmp;
	char		*cpy;
	int			aux;

	tmp = -1;
	nb = NULL;
	cpy = ft_strdup("SHLVL=");
	while (environ[++tmp])
	{
		if (ft_strncmp(environ[tmp], "SHLVL", 5) == 0)
		{
			aux = ft_atoi(environ[tmp] + 6) + 1;
			nb = ft_itoa(aux);
			environ[tmp] = ft_strjoin(cpy, nb);
			break ;
		}
	}
}

void	msg_exit(void)
{
	printf ("\e[A\e[K");
	printf("minishell: exit\n");
	exit(0);
}

char	**cpy_matrix(char **matrix, int offset)
{
	int		i;
	int		c;
	char	**ret;
	int		size;

	i = -1;
	c = 0;
	while (matrix[++i])
	{
		if (matrix[i][0] != '\0')
			c++;
	}
	size = c - offset;
	ret = (char **)malloc(sizeof(char *) * size);
	i = 0;
	c = 0;
	while (i < size && matrix[i])
	{
		if (matrix[i][0] == '\0')
			i++;
		else
			ret[c++] = ft_strdup(matrix[i++]);
	}
	ret[c] = NULL;
	return (ret);
}
