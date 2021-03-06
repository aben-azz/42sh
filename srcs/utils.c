/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 19:09:23 by midrissi          #+#    #+#             */
/*   Updated: 2019/05/24 15:33:28 by midrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	print_prompt(void)
{
	ft_printf(ANSI_BBLUE "-> " ANSI_RESET);
	ft_printf(ANSI_BCYAN "%s" ANSI_RESET, "42sh");
	ft_printf(ANSI_BBLUE "> "ANSI_RESET);
}

void ft_exit(char *str)
{
	ft_putendl_fd(str, 2);
	exit(1);
}
void	sigfork(int sig)
{
	if (sig == SIGINT)
	{
		ft_putchar('\n');
		signal(SIGINT, sigfork);
	}
}

void	sighandler(int sig)
{
	if (sig == SIGINT)
	{
		ft_putchar('\n');
		signal(SIGINT, sighandler);
	}
}
