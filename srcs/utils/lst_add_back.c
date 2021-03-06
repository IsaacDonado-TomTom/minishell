/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lst_add_back.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwray <lwray@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/02 20:44:27 by lwray         #+#    #+#                 */
/*   Updated: 2021/10/02 20:44:28 by lwray         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	**lst_add_back(t_token **list, t_token *new)
{
	t_token	*last;

	if (new == NULL)
		return ((void *) NULL);
	if (*list)
	{
		last = lst_last(*list);
		if (last)
		{
			new->previous = last;
			last->next = new;
		}
	}
	else if (list)
		*list = new;
	return (list);
}

void	cmd_lst_add_back(t_cmd_lst **list, t_cmd_lst *new)
{
	t_cmd_lst	*last;

	if (*list)
	{
		last = cmd_lst_last(*list);
		if (last)
		{
			new->previous = last;
			last->next = new;
		}
	}
	else if (list)
		*list = new;
}

void	env_lst_add_back(t_env_lst **list, t_env_lst *new)
{
	t_env_lst	*last;

	if (*list)
	{
		last = env_lst_last(*list);
		if (last)
		{
			new->previous = last;
			last->next = new;
		}
	}
	else if (list)
		*list = new;
}
