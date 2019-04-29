/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 19:09:23 by midrissi          #+#    #+#             */
/*   Updated: 2019/04/29 19:09:33 by midrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	print_prompt(void)
{
	char	buff[MAX_PATH_LEN];
	int		i;
	int		j;

	i = -1;
	j = 0;
	ft_bzero(buff, MAX_PATH_LEN);
	getcwd(buff, MAX_PATH_LEN);
	while (buff[++i])
		if (buff[i] == '/' && buff[i + 1])
			j = i + 1;
	ft_printf(ANSI_BLUE "-> " ANSI_RESET);
	ft_printf(ANSI_CYAN "%s" ANSI_RESET, buff + j);
	ft_printf(ANSI_BLUE "> "ANSI_RESET);
}
