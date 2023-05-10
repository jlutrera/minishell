/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpachec <adpachec@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 12:32:44 by adpachec          #+#    #+#             */
/*   Updated: 2023/03/29 10:37:25 by adpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	there_are_args(t_token *token_list)
{
	int		i;
	t_token	*p;

	i = 0;
	p = token_list->next;
	while (p)
	{
		i++;
		p = p->next;
	}
	if (i > 0)
	{
		ft_putstr_fd("minishell: env: Too many arguments\n", STDERR_FILENO);
		return (127);
	}
	return (0);
}

static int	ft_exist_equal(char *s)
{
	int	i;

	i = -1;
	while (s[++i])
	{
		if (s[i] == '=')
			break ;
	}
	return (s[i] == '=');
}

int	ft_env(t_token *token_list, char ***new_environ, int is_pipe)
{
	int	i;
	int	status;

	status = 0;
	if (!(*new_environ) || !(*new_environ[0]))
		status = -1;
	else if (!there_are_args(token_list))
	{
		i = -1;
		while ((*new_environ)[++i])
		{
			if (ft_exist_equal((*new_environ)[i]))
			{
				ft_putstr_fd((*new_environ)[i], STDOUT_FILENO);
				ft_putchar_fd('\n', STDOUT_FILENO);
			}
		}
	}
	else
		status = 127;
	if (is_pipe)
		exit(status);
	return (status);
}
