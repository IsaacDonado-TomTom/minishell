#include "../../includes/minishell.h"

t_data  g_data;

static  t_env_lst   *sort_env_lst(t_env_lst *lst)
{
    t_env_lst   *sort_i;
    t_env_lst   *sort_j;
    char        *temp_str;

    sort_i = lst;
    while (sort_i)
    {
        sort_j = sort_i->next;
        while (sort_j)
        {
            if (ft_strcmp(sort_i->key, sort_j->key) > 0)
            {
                temp_str = sort_i->key;
                sort_i->key = sort_j->key;
                sort_j->key = temp_str;
            }
            sort_j = sort_j->next;
        }
        sort_i = sort_i->next;
    }
    return (lst);
}

static int ft_export_noarg(int fd_out)
{
    t_env_lst   *temp;
    t_env_lst   *new;
    t_env_lst   *lst;

    temp = g_data.env_lst;
    lst = NULL;
    while (temp)
    {
        new = env_lst_new(ft_strdup(temp->key), ft_strdup(temp->value));
        env_lst_add_back(&lst, new);
        temp = temp->next;
    }
    lst = sort_env_lst(lst);
    while (lst)
    {
        if (ft_cinstr(lst->value, ' ') == 1 || ft_strlen(lst->value) == 0)
            ft_dprintf(fd_out, "declare -x %s='%s'\n", lst->key, lst->value);
        else
            ft_dprintf(fd_out, "declare -x %s=%s\n", lst->key, lst->value);
        temp = lst;
        lst = lst->next;
        free(temp->key);
        free(temp->value);
        free(temp);
    }
    return (0);
}

static int ft_export_eql(char *cmd, int fd_out)
{
    char    **temp;
    int     ret;

    if (cmd[0] == '=')
    {
        ft_dprintf(fd_out, "export: not valid in this context\n");
        return (2);
    }
    else
    {
        temp = ft_split(cmd, '=');
        if (temp[1] == NULL)
            temp[1] = ft_strdup("");
        if (ft_isalpha(temp[0][0]) == 0)
        {
            ft_dprintf(fd_out, "export, not an identifier: %s\n", temp[0]);
            ft_split_free(temp);
            return (2);
        }
        else if (ft_isalnum_str(temp[0]) == 0)
        {
            ft_dprintf(fd_out, "export, not valid in this context: %s\n", temp[0]);
            ft_split_free(temp);
            return (2);
        }
        else if (export_exists(temp[0], temp[1]) == 1)
            ft_split_free(temp);
        else
        {
            ret = ft_export_add(temp[0], temp[1]);
			ft_split_free(temp);
            return (ret);
        }
    }
    return (0);
}

static int ft_export_key(char *cmd, int fd_out)
{
    if (ft_isdigit(cmd[0]) == 1)
    {
        ft_dprintf(fd_out, "export, not an identifier: %s\n", cmd);
        return (2);
    }
    else if (ft_isalnum_str(cmd) == 0)
    {
        ft_dprintf(fd_out, "export, not valid in this context: %s\n", cmd);
        return (2);
    }
    else if (export_exists_key(cmd) == 1)
        return (0);
    else
        return (ft_export_add(cmd, ""));
    return (0);
}

int    ft_export(char **cmd, int fd_out)
{
    int i;
    int ret;

    (void)fd_out;
    if (cmd[1] == NULL)
        return (ft_export_noarg(fd_out));
    else
    {
        i = 1;
        while (cmd[i])
        {
            if (ft_cinstr(cmd[i], '=') == 1)
                ret = ft_export_eql(cmd[i], fd_out);
            else
                ret = ft_export_key(cmd[i], fd_out);
            if (ret != 0)
                return (ret);
            i++;
        }
    }
    return (0);
}
