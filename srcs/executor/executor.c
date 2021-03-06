/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 16:15:41 by midrissi          #+#    #+#             */
/*   Updated: 2019/05/25 13:46:53 by midrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		exec_builtin(char **builtin, int id, char ***env)
{
	int	ac;
	int	err_id;

	ac = ft_split_count(builtin);
	err_id = 0;
	if (id == ECHO_BUILTIN)
		err_id = echo_builtin(ac, builtin);
	if (id == CD_BUILTIN)
		err_id = cd_builtin(ac, builtin, env);
	if (id == ENV_BUILTIN && ac == 1)
		print_env(*env);
	if (id == SETENV_BUILTIN)
		err_id = setenv_builtin(ac, builtin, env);
	if (id == UNSETENV_BUILTIN)
		err_id = unsetenv_builtin(ac, builtin, env);
	if (id == EXIT_BUILTIN)
		exit_builtin();
	if (err_id)
		err_handler(err_id, builtin[0]);
	return (err_id);
}

static void		ft_execute(char **args, int redir)
{
	int builtin;

	g_shell->lastsignal = ft_pre_execution(&args, redir, &builtin);
	if (!g_shell->lastsignal && !builtin)
		g_shell->lastsignal = ft_fork(args, g_shell->env);
	if (!g_shell->lastsignal && builtin)
		g_shell->lastsignal = exec_builtin(args, builtin, &g_shell->env);
	if (redir)
		restore_fd();
}

void	ft_execute_ast(t_ast *root, char **env)
{
	if (!root)
		return ;
	if (root->token->op_type == PIPE)
	{
		handle_pipe(root);
		return ;
	}
	if (root->left)
		ft_execute_ast(root->left, env);
	if (root->left && root->token->op_type == DBL_AND && g_shell->lastsignal)
		return ;
	if (root->left && root->token->op_type == DBL_PIPE && !g_shell->lastsignal)
		return ;
	if (root->right)
		ft_execute_ast(root->right, env);
	if (root->token->type == TOKEN_WORD)
		ft_execute(root->token->content, root->token->redir);
}
