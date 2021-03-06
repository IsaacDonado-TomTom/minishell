/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_cd_utils_a.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: idonado <idonado@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/04 14:34:06 by idonado       #+#    #+#                 */
/*   Updated: 2021/10/04 14:34:06 by idonado       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_data	g_data;

void	ft_cd_a(char **cmd)
{
	char	*temp_str;

	if (cmd[1][0] == '~')
	{
		cmd[1]++;
		temp_str = ft_strjoin((ft_get_env_var("HOME"))->value, cmd[1]);
		cmd[1]--;
		free(cmd[1]);
		cmd[1] = temp_str;
	}
	return ;
}

void	ft_cd_b(int *ret, int *msg, int fd_out)
{
	t_env_lst	*temp;

	temp = ft_get_env_var("OLDPWD");
	if (!temp)
	{
		*msg = 1;
		ft_dprintf(fd_out, "cd: OLDPWD not set\n");
		*ret = 1;
	}
	else
	{
		if (!(temp->value))
		{
			*msg = 1;
			ft_dprintf(fd_out, "cd: OLDPWD not set\n");
			*ret = 1;
		}
		else
		{
			*ret = chdir(temp->value);
			ft_dprintf(fd_out, "%s\n", temp->value);
		}
	}
	return ;
}

void	ft_cd_c(char **cmd, char *oldpwd, int msg, int *ret)
{
	if (!msg)
	{
		if (errno == ENOTDIR)
			ft_dprintf(STDERR_FILENO, "cd: %s: Not a directory\n", cmd[1]);
		else if (ft_strlen(cmd[1]) > PATH_MAX)
			ft_dprintf(STDERR_FILENO, \
			"cd: %s: File name too long\n", cmd[1]);
		else if (errno == ENOENT)
		{
			ft_dprintf(STDERR_FILENO, \
			"cd: %s: No such file or directory\n", cmd[1]);
			*ret = 1;
		}
	}
	free(oldpwd);
	return ;
}

int	ft_cd_d(void)
{
	t_cmd_lst	*temp;

	temp = g_data.cmd_lst;
	while (temp)
	{
		if (ft_streql(temp->subcmd.cmd[0], "pwd") == 1)
			return (1);
		temp = temp->next;
	}
	return (0);
}
