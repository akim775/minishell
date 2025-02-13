/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamini <ahamini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 10:48:17 by ahamini           #+#    #+#             */
/*   Updated: 2025/02/11 10:48:20 by ahamini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	increment_all_cmd_index(t_list *start)
{
	t_list	*current;
	t_cmd	*curr_cmd;

	current = start;
	while (current != NULL)
	{
		curr_cmd = ((t_cmd *)current->content);
		curr_cmd->cmd_index++;
		current = current->next;
	}
}

t_cmd	*create_cmd(void)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)ft_calloc(sizeof(t_cmd), 1);
	if (!cmd)
		return (NULL);
	cmd->fork_pid = -1;
	cmd->fd_in = -1;
	cmd->fd_out = -1;
	return (cmd);
}

void	create_file(t_shell *shell, t_cmd *cmd, t_token *token)
{
	t_file	*file;
	t_list	*node;

	file = (t_file *)ft_calloc(sizeof(t_file), 1);
	if (!file)
		return (set_error(MALLOC_FAIL, shell, "Failed to allocate filename"));
	file->mode = token->lexem;
	file->path = ft_strdup(token->content);
	if (!file->path)
		return (set_error(MALLOC_FAIL, shell, "Failed to allocate filename"));
	node = ft_lstnew(file);
	if (!node)
		return (set_error(MALLOC_FAIL, shell, "Failed to alloc file node"));
	if (file->mode == HEREDOC)
	{
		file->delim = file->path;
		file->path = generate_heredoc_filepath(shell);
		if (!file->path)
			return (set_error(MALLOC_FAIL, shell, "Failed hered generation"));
	}
	if (file->mode == INFILE || file->mode == HEREDOC)
		ft_lstadd_back(&cmd->infiles, node, 0);
	if (file->mode == OUTFILE || file->mode == APPEND)
		ft_lstadd_back(&cmd->outfiles, node, 0);
}

t_shell	*create_minishell(char **env)
{
	t_shell	*shell;

	shell = ft_calloc(sizeof(t_shell), 1);
	if (!shell)
		return (NULL);
	shell->env = env;
	if (extract_paths(shell) == -1)
	{
		free(shell);
		return (NULL);
	}
	dup2(STDOUT_FILENO, shell->std_out);
	dup2(STDIN_FILENO, shell->std_in);
	extract_env_as_linked_list(shell);
	return (shell);
}
