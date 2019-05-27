/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   completion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 06:02:13 by aben-azz          #+#    #+#             */
/*   Updated: 2019/05/27 05:40:50 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		init_autocomp(t_ab *autocomp)
{
	int max_offset;

	max_offset = autocomp->max_offset;
	autocomp->row = g_shell->tcap->cursx_max / (max(max_offset + 2, 1));
	autocomp->col = autocomp->len / max(autocomp->row, 1);
	autocomp->carry = autocomp->len % max(autocomp->row, 1);
	return (max_offset);
}

int		print_name(t_ab *autocomp, char *str, int i)
{
	dprintf(debug(), " euuh xd %d %d\n", i, autocomp->pos);
	if (i == autocomp->pos)
		ft_putstr("\x1b[7m");
	ft_putstr(str);
	if (i == autocomp->pos)
		ft_putstr("\x1b[0m");
	ft_move(g_shell->tcap, "!right", autocomp->max_offset - ft_strlen(str) + 2);
	return (1);
}

static void		cat_fullpath(t_file *file, char *name, char *path)
{
	ft_bzero((void *)&(file->full_path), MAX_PATH);
	if (path)
	{
		ft_strcpy(file->full_path, path);
		if (*path != '/' || *(path + 1))
			ft_strcat(file->full_path, "/");
	}
	ft_strcat(file->full_path, name);
	file->name = ft_strdup(name);
	!file->name ? exit(1) : 0;
	file->path = path;
}

t_file			create_file(char *name, char *path)
{
	t_file		file;

	ft_bzero((void *)&file, sizeof(t_file));
	cat_fullpath(&file, name, path);
	lstat(file.full_path, &(file.stats));
	return (file);
}

void		get_words_completion(t_ab *autocomp, char *path)
{
	t_dirent	*d;
	DIR			*dir;

	autocomp->len = 0;
	autocomp->max_offset = 0;
	ft_bzero(autocomp->data, sizeof(autocomp->data));
	if ((dir = opendir(".")))
		while ((d = readdir(dir)))
		{
			if (d->d_name[0] != '.')
			{
				autocomp->data[autocomp->len] = create_file(d->d_name, path);
				autocomp->max_offset =
								max(autocomp->max_offset, ft_strlen(d->d_name));
				autocomp->len++;
			}
		}
	closedir(dir);
}

int		ft_tab(t_cap *tcap, t_ab *autocomp)
{
	int row;
	int col;
	int i;
	char *command;

	get_words_completion(autocomp, ".");
	init_autocomp(autocomp);
	i = 0;
	col = -1;
	ft_move(tcap, "down", 2);
	while (++col < autocomp->col)
	{
		row = -1;
		while (++row < autocomp->row)
			print_name(autocomp, autocomp->data[i].name, i) && i++;
		ft_move(tcap, "down", 1);
	}
	if (autocomp->carry > 0)
	{
		row = autocomp->carry;
		while (row--)
			print_name(autocomp, autocomp->data[i].name, i) && i++;
	}
	//ft_replace_cursor(tcap);
	ft_move(tcap, "up", autocomp->col + (autocomp->carry > 0 ? 1 : +1) + 1);
	command = ft_strjoin(autocomp->match, g_shell->autocomp->data[g_shell->autocomp->pos].name);
	ft_clear_replace(tcap);
	ft_insert(command, tcap);
	return (1);
}
