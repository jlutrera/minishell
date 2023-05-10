/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpachec <adpachec@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 12:42:02 by adpachec          #+#    #+#             */
/*   Updated: 2023/03/30 11:19:32 by adpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static enum e_token_type	get_token_type(const char *token, int len)
{
	if (*token == '-')
		return (ARGUMENT);
	else if (ft_strcmp(token, "|") == 0)
		return (PIPE);
	else if (*token == '\"' && token[ft_strlen(token) - 1] == '\"')
		return (DOUBLE_QUOTE);
	else if (*token == '\'' && token[ft_strlen(token) - 1] == '\'')
		return (SINGLE_QUOTE);
	else if (*token == '$')
		return (VARIABLE);
	else
		return (check_builtin(token, len));
	return (COMMAND);
}

static enum e_token_type	get_heredoc_type(char *input, int len)
{
	int	i;

	i = -1;
	while (++i < len)
	{
		if (ft_is_quote(input[i]))
			return (HEREDOC_QUOTE);
	}
	return (HEREDOC_REDIRECT);
}

static enum e_token_type	get_type_redirect(const char *token, char *input,
												int len)
{
	if (ft_strncmp(token, ">>", 2) == 0)
		return (APPEND_REDIRECT);
	else if (ft_strncmp(token, "<<", 2) == 0)
		return (get_heredoc_type(input, len));
	else if (ft_strncmp(token, "<", 1) == 0)
		return (INPUT_REDIRECT);
	else if (ft_strncmp(token, ">", 1) == 0)
		return (OUTPUT_REDIRECT);
	return (COMMAND);
}

static t_token	*add_token_to_list(t_token **list, char *input, int len, \
char *token)
{
	t_token	*new_token;

	if (!input)
		return (NULL);
	new_token = (t_token *)ft_calloc(sizeof(t_token), 1);
	if (!input)
		exit_error(errno);
	input = input - len;
	new_token->token = ft_substr(input, 0, len);
	while (ft_is_space(*token))
		++token;
	if (ft_is_redirect(*token))
		new_token->type = get_type_redirect(token, input, len);
	else
		new_token->type = get_token_type(new_token->token, len);
	if (*list == NULL)
		*list = new_token;
	else
		ft_token_add_back(list, new_token);
	return (*list);
}

t_token	*tokenize_input(char *input, char **env)
{
	t_token	*token_list;
	char	*token;
	int		len;	

	if (!input)
		return (NULL);
	token_list = NULL;
	add_history(input);
	while (*input)
	{
		token = (char *) input;
		len = ft_reading_token(&input);
		if (len < 0)
		{
			exit_error_token(len, token);
			free_tokens(&token_list);
			return (NULL);
		}
		else if (len)
			add_token_to_list(&token_list, input, len, token);
	}
	ft_check_vars(&token_list, env);
	return (token_list);
}
