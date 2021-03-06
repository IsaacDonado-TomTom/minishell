/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   syntax_error.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwray <lwray@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/02 18:19:04 by lwray         #+#    #+#                 */
/*   Updated: 2021/10/02 18:19:06 by lwray         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	invalid_io_file_char(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (1);
	return (0);
}

int	set_syntax_error(char *msg)
{
	char	*str;

	str = "minishell: syntax error near unexpected token ";
	dprintf(STDERR_FILENO, "%s`%s'\n", str, msg);
	export_exists("?", "2");
	return (EXIT_FAILURE);
}

int	file_check(char *file)
{
	if (invalid_io_file_char(*file))
		return (set_syntax_error(file));
	else if (!*file)
		return (set_syntax_error("newline"));
	return (EXIT_SUCCESS);
}

int	syntax_error(t_token *token_lst, t_cmd_lst *cmd_lst)
{
	t_cmd_lst	*lst;

	lst = cmd_lst;
	while (lst)
	{
		if ((!*lst->subcmd.cmd && lst->subcmd.in_type == VOID
				&& lst->subcmd.out_type == VOID)
			|| lst_last(token_lst)->type == PIPE)
			return (set_syntax_error("|"));
		if ((lst->subcmd.in_type == INPUT_REDIRECTION
				|| lst->subcmd.in_type == HEREDOC)
			&& file_check(lst->subcmd.in_file))
			return (EXIT_FAILURE);
		if ((lst->subcmd.out_type == OUTPUT_REDIRECTION
				|| lst->subcmd.out_type == APPEND)
			&& file_check(lst->subcmd.out_file))
			return (EXIT_FAILURE);
		lst = lst->next;
	}
	return (EXIT_SUCCESS);
}
