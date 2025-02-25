/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamini <ahamini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 10:50:04 by ahamini           #+#    #+#             */
/*   Updated: 2025/02/24 13:31:01 by ahamini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	main(int argc, char **argv, char **envp)
// {
// 	t_shell	*shell;
// 	char	*false_argv[2] = {"export", NULL};

// 	shell = create_minishell(envp);
// 	if (argc > 1)
// 	{
// 		export(shell, &argv[1], STDOUT_FILENO);
// 		fprintf(stderr, "export done\n\n");
// 		export(shell, false_argv, STDOUT_FILENO);
// 		unset(shell, &argv[1]);
// 		fprintf(stderr, "unset done\n\n");
// 		export(shell, false_argv, STDOUT_FILENO);
// 	}
// 	return (0);
// }

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
