/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_environ.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpachec <adpachec@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 12:46:20 by adpachec          #+#    #+#             */
/*   Updated: 2023/03/27 13:24:45 by adpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**env_creation(void)
{
	char	dir[1024];
	char	**d;

	d = (char **)ft_calloc(3, sizeof(char *));
	if (!d)
		return (0);
	d[0] = ft_strdup("SHLVL=1");
	if (getcwd(dir, sizeof(dir)) != NULL)
		d[1] = ft_strdup(dir);
	return (d);
}

char	**copy_environ(char **source)
{
	char	**dest;
	int		len;
	int		i;

	if (source && *source)
	{
		len = 0;
		while (source[len])
			len++;
		dest = (char **)ft_calloc(len + 1, sizeof(char *));
		if (!dest)
			return (0);
		i = -1;
		while (source[++i])
			dest[i] = ft_strdup(source[i]);
		dest[i] = 0;
	}
	else
		dest = env_creation();
	return (dest);
}
