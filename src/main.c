/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamini <ahamini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 10:50:04 by ahamini           #+#    #+#             */
/*   Updated: 2025/02/26 16:48:08 by ahamini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

pid_t	g_signal_pid;

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	(void)argc;
	(void)argv;
	shell.env = NULL;
	shell.token = NULL;
	shell.cmd = NULL;
	shell.exit_code = 0;
	shell.pip[0] = -1;
	shell.pip[1] = -1;
	g_signal_pid = 0;
	signals();
	if (!create_minishell(&shell, envp))
		free_all(&shell, ERR_MALLOC, EXT_MALLOC);
	init_readline(&shell);
	return (0);
}
