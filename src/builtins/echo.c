/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eblancha <eblancha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 09:19:21 by skassimi          #+#    #+#             */
/*   Updated: 2025/02/26 10:44:02 by eblancha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_new_line(char *str)
{
	int	i;

	i = 0;
	if (str[i] && str[i] == '-')
	{
		++i;
		while (str[i] && str[i] == 'n')
			i++;
		if (i == (int)ft_strlen(str))
			return (1);
	}
	return (0);
}

static void	write_echo(int count, int i, bool new_line, char **args)
{
	while (args[i] && check_new_line(args[i]))
	{
		++i;
		new_line = false;
	}
	while (i < count)
	{
		write(1, args[i], ft_strlen(args[i]));
		if (i != count - 1)
			write(1, " ", 1);
		++i;
	}
	if (new_line)
		write(1, "\n", 1);
}

int	echo(char **args)
{
	int		count;
	int		i;
	bool	new_line;

	count = 0;
	while (args[count])
		++count;
	i = 1;
	new_line = true;
	write_echo(count, i, new_line, args);
	return (0);
}
