/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamini <ahamini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 10:48:56 by ahamini           #+#    #+#             */
/*   Updated: 2025/02/11 10:48:58 by ahamini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	get_token_count(t_list *start, t_list *end)
{
	t_list	*current;
	size_t	count;

	current = start;
	count = 0;
	while (current != end)
	{
		count++;
		current = current->next;
	}
	return (count);
}

size_t	count_tokens_of_type(t_list *start, int lexem)
{
	t_list	*current;
	size_t	count;

	current = start;
	count = 0;
	while (((t_token *)current->content)->lexem != END)
	{
		if (((t_token *)current->content)->lexem == lexem)
			count++;
		current = current->next;
	}
	return (count);
}

char	**extract_token_as_array(t_shell *shell, t_list *start, int type)
{
	int		index;
	int		count;
	char	**result;

	count = count_tokens_of_type(start, type);
	if (count == 0)
		return (NULL);
	result = ft_calloc(sizeof(char *), count + 1);
	if (!result)
		return (set_error(MALLOC_FAIL, shell,
				"Failed to allocate infile path"), NULL);
	index = 0;
	while (((t_token *)start->content)->lexem != END)
	{
		if (((t_token *)start->content)->lexem == type)
			result[index++] = ft_strdup(((t_token *)start->content)->content);
		start = start->next;
	}
	result[index] = NULL;
	return (result);
}

void	id_variables(t_shell * shell, t_list *current)
{
	if (catch_error(shell)
		|| ((t_token *)current->content)->lexem != OPERATOR)
		return ;
	if (((t_token *)current->content)->letter == '$')
	{
		current = current->next;
		((t_token *)current->content)->lexem = VARIABLE;
		ft_lstpop(&shell->token_list, current->prev, free_token);
	}
}

void	lexer(t_shell *shell)
{
	scan(shell);
	// print_tokens(shell->token_list);
}

// TO DO
// escape character
// when to expand variables
// id variables

