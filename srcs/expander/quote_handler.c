/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   quote_handler.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwray <lwray@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/02 18:18:31 by lwray         #+#    #+#                 */
/*   Updated: 2021/10/02 18:18:34 by lwray         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*add_string(char *str1, char *str2)
{
	char	*joined_str;

	if (str2)
	{
		joined_str = ft_strjoin(str1, str2);
		free (str1);
		free (str2);
		return (joined_str);
	}
	return (str1);
}

void	skip_over_quotes(char *str, int *i)
{
	if (str[*i] == '"')
	{
		(*i)++;
		while (str[*i] != '"' && str[*i] != '\0')
			(*i)++;
	}
	if (str[*i] == '\'')
	{
		(*i)++;
		while (str[*i] != '\'' && str[*i] != '\0')
			(*i)++;
	}
	(*i)++;
}

char	*quote_handler(char *cmd)
{
	char	*str;
	int		start;
	int		i;
	int		j;

	i = 0;
	start = i;
	str = ft_strdup("");
	while (cmd[i])
	{
		if (cmd[i] == '"' || cmd[i] == '\'')
		{
			j = i;
			skip_over_quotes(cmd, &i);
			str = add_string(str, ft_substr(cmd, start, j - start));
			str = add_string(str, ft_substr(cmd, j + 1, i - j - 2));
			start = i;
			continue ;
		}
		i++;
	}
	str = add_string(str, ft_substr(cmd, start, i - start));
	free (cmd);
	return (str);
}
