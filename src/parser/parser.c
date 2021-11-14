#include "cub3d.h"

int	list_to_2d_map_nested(t_re *re, t_list **tmpl)
{
	int		i;
	t_list	*tmplptr;
	int		linelen;

	tmplptr = *tmpl;
	i = -1;
	while (++i < re->map.map_height)
	{
		if (!(new_mem_assign(&re->mm, (void **)&re->map.m[i],
					re->map.map_width + 1)))
		{
			ft_lstclear(tmpl, free);
			return (emsg(-1, "Malloc (char*) error!"));
		}
		linelen = ft_strlen(tmplptr->content);
		ft_memmove(re->map.m[i], tmplptr->content, linelen);
		ft_memset(re->map.m[i] + linelen, ' ', re->map.map_width - linelen);
		re->map.m[i][re->map.map_width] = 0;
		tmplptr = tmplptr->next;
	}
	return (0);
}

int	list_to_2d_map(t_re *re, t_list **tmpl)
{
	if (!(new_mem_assign(&re->mm, (void **)&re->map.m,
				(re->map.map_height) * sizeof(char*))))
	{
		ft_lstclear(tmpl, free);
		return (emsg(-1, "Malloc (char**) error!"));
	}
	if (list_to_2d_map_nested(re, tmpl) < 0)
		return (-1);
	return (0);
}

int	open_map(t_re *re, char *path)
{
	int		fd;
	char	*line;
	t_list	*tmpl;

	if (check_map_path(path) < 0)
		return (-1);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (emsg(-1, "Can't open the map!"));
	if (read_params(re, fd) < 0
		|| read_empty_lines(fd, &line) < 0
		|| read_map_list(re, &line, fd, &tmpl) < 0
		|| list_to_2d_map(re, &tmpl) < 0)
		return (-1);
	close(fd);
	ft_lstclear(&tmpl, free);
	if (locate_player(re) < 0
		|| locate_sprites(re) < 0)
		return (-1);
	if (map_close_check_2(re) < 0
		|| map_close_check(re) < 0)
		return (emsg(-1, "Map is not closed!"));
	map_decode(re);
	return (0);
}
