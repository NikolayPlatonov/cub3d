#include "../../include/cub3d.h"

static	int	add_to_list(t_list *lst, int x, int y)
{
	t_list		*tmp;
	t_list		*last;
	t_ipoint	*content;

	content = malloc(sizeof(t_ipoint));
	if (!content)
		return (emsg(-1, "Malloc error!"));
	content->x = x;
	content->y = y;
	tmp = ft_lstnew(content);
	if (!tmp)
	{
		free(content);
		return (emsg(-1, "Malloc error!"));
	}
	last = ft_lstlast(lst);
	last->next = tmp;
	return (0);
}

static	int	map_encode(t_re *re, int x, int y)
{
	if (ft_strchr(" 0NSWE", re->map.m[y][x]))
		re->map.m[y][x] = 'a';
	else if (re->map.m[y][x] == '1')
		re->map.m[y][x] = 'b';
	else if (re->map.m[y][x] == '2')
		re->map.m[y][x] = 'c';
	return (1);
}

static	int	map_close_check_loop_nested(t_re *re, t_list **lst, int x, int y)
{
	if (!ft_strchr("abc1", re->map.m[y][x + 1])
		&& map_encode(re, x + 1, y))
		if (add_to_list(*lst, x + 1, y) < 0)
			return (-1);
	if (!ft_strchr("abc1", re->map.m[y][x - 1])
		&& map_encode(re, x - 1, y))
		if (add_to_list(*lst, x - 1, y) < 0)
			return (-1);
	if (!ft_strchr("abc1", re->map.m[y + 1][x])
		&& map_encode(re, x, y + 1))
		if (add_to_list(*lst, x, y + 1) < 0)
			return (-1);
	if (!ft_strchr("abc1", re->map.m[y - 1][x])
		&& map_encode(re, x, y - 1))
		if (add_to_list(*lst, x, y - 1) < 0)
			return (-1);
	return (0);
}

static	int	map_close_check_loop(t_re *re, t_list **lst)
{
	int		x;
	int		y;
	t_list	*tmp;

	while (*lst)
	{
		x = ((t_ipoint *)((*lst)->content))->x;
		y = ((t_ipoint *)((*lst)->content))->y;
		if (is_map_break(re, x + 1, y) || is_map_break(re, x, y + 1)
			|| is_map_break(re, x - 1, y) || is_map_break(re, x, y - 1))
			return (-1);
		if (map_close_check_loop_nested(re, lst, x, y) < 0)
			return (-1);
		map_encode(re, x, y);
		tmp = *lst;
		*lst = (*lst)->next;
		ft_lstdelone(tmp, &free);
	}
	return (0);
}

int	map_close_check(t_re *re)
{
	t_list		*lst;
	t_ipoint	*ipoint_tmp;

	ipoint_tmp = malloc(sizeof(t_ipoint));
	if (!ipoint_tmp)
		return (emsg(-1, "Malloc (t_ipoint) error!"));
	ipoint_tmp->x = (int)re->player_pos.y;
	ipoint_tmp->y = (int)re->player_pos.x;
	lst = ft_lstnew(ipoint_tmp);
	if (!lst)
		return (emsg(-1, "Malloc ft_lstnew error!"));
	if (map_close_check_loop(re, &lst))
	{
		ft_lstclear(&lst, free);
		return (-1);
	}
	return (0);
}
