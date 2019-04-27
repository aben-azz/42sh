/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 17:44:52 by midrissi          #+#    #+#             */
/*   Updated: 2019/04/27 17:34:47 by midrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

void	sighandler(int sig)
{
	if (sig == SIGINT)
	{
		ft_printf("\n");
		exit(1);
		signal(SIGINT, sighandler);
	}
}

void 		pipe_cmds(char **cmd1, char **cmd2, char **env)
{
	int fildes[2];
	pid_t pid;

	pipe(fildes);
	pid = fork();
	signal(SIGINT, sighandler);
	if (pid == 0)
	{
		close(fildes[0]);
		dup2(fildes[1], 1); /* recupere stdout de ma 1ere commande */
		dup2(fildes[1], 2); /* recupere stderr de ma 2eme commande */
		execve(cmd1[0], cmd1, env);
	}
	pid = fork();
	signal(SIGINT, sighandler);
	if (pid == 0)
	{
		close(fildes[1]);
		dup2(fildes[0], 0); /* recupere la sortie de pipe dans stdin de ma 2 eme commande */
		execve(cmd2[0], cmd2, env);
	}
	wait(&pid);
	close(fildes[0]);
	close(fildes[1]);
	return ;
}

/*
** petit example pour recuperer stdin & err dans un fork
*/
int main(int argc, char **argv, char **env)
{
	char **cmd1;
	char **cmd2;

	cmd1 = (char **)malloc(sizeof(char *) * 4);
	cmd1[0] = "/bin/ls";
	cmd1[1] = "-R";
	cmd1[2] = "/";
	cmd1[3] = NULL;
	cmd2 = (char **)malloc(sizeof(char *) * 4);
	cmd2[0] = "/usr/bin/grep";
	cmd2[1] = "--color=always";
	cmd2[2] = "Desktop";
	cmd2[3] = NULL;
	pipe_cmds(cmd1, cmd2, env);
	return (0);
}







/*
** REDIRECTION DANS UN FICHIER DONNER DANS ARGV[1]
*/
// int main(int argc, char **argv)
// {
// 	// int fildes[2];
// 	pid_t pid;
// 	char **str;
// 	char buff[300];
//
// 	int fd = open(argv[1], O_RDONLY | O_WRONLY | O_TRUNC | O_CREAT, 0666);
// 	str = (char **)malloc(sizeof(char *) * 4);
// 	str[0] = ft_strdup("/bin/ls");
// 	str[1] = ft_strdup(".");
// 	str[2] = ft_strdup("hadhgawjh");
// 	str[3] = NULL;
// 	// pipe(fildes);
// 	dup2(fd, 1); /* recupere stdout */
// 	dup2(fd, 2); /* recupere stderr */
// 	execve("/bin/ls", str, NULL);
// 	return (0);
// }
