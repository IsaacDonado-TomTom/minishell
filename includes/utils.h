#ifndef UTILS_H
# define UTILS_H

#include <stdlib.h>
#include "types.h"

char	*ft_substr(char const *s, unsigned int start, size_t len);
void	lst_add_back(t_token **list, t_token *new);
void	cmd_lst_add_back(t_cmd_lst **list, t_cmd_lst *new);
t_token	*lst_new(char *content, t_type type);
t_cmd_lst	*cmd_lst_new(t_subcmd subcmd);
t_token	*lst_last(t_token *last);
t_cmd_lst	*cmd_lst_last(t_cmd_lst *last);
int		ft_strlen(char *str);

#endif