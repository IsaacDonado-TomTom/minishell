/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   getenv.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwray <lwray@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/02 20:36:08 by lwray         #+#    #+#                 */
/*   Updated: 2021/10/06 18:37:56 by idonado       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

static t_env_lst	*get_shell_lvl(t_env_lst *temp)
{
	while (temp)
	{
		if (ft_streql(temp->key, "SHLVL") == 1)
			return (temp);
		temp = temp->next;
	}
	return (temp);
}

static void	set_shell_lvl(t_env_lst *lst)
{
	t_env_lst	*temp;
	int			level;

	temp = get_shell_lvl(lst);
	if (temp && temp->value)
	{
		level = ft_atoi(temp->value);
		level++;
		free(temp->value);
		temp->value = ft_itoa(level);
	}
}

t_env_lst	*ft_getenv(char **env)
{
	t_env_lst	*env_lst;
	t_env_lst	*env_new;
	char		**temp;
	int			i;

	env_lst = NULL;
	i = 0;
	while (env[i] != NULL)
	{
		temp = ft_split(env[i], '=');
		env_new = env_lst_new(ft_strdup(temp[0]), ft_strdup(temp[1]));
		env_lst_add_back(&env_lst, env_new);
		ft_free_array(temp);
		i++;
	}
	set_shell_lvl(env_lst);
	return (env_lst);
}
