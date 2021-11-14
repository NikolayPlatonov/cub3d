#include "../include/cub3d.h"

int	map_line_err(char *line)
{
	int			i;
	static int	player_pos_flag;

	i = 0;
	while (line[i])
	{
		if (line[i] != '0' && line[i] != '1'
			&& line[i] != '2' && line[i] != ' '
			&& line[i] != 'N' && line[i] != 'S'
			&& line[i] != 'E' && line[i] != 'W')
			return (emsg(1, "Incorrect map character!"));
		if (line[i] == 'N' || line[i] == 'S'
			|| line[i] == 'E' || line[i] == 'W')
		{
			if (!player_pos_flag)
				player_pos_flag = 1;
			else
				return (emsg(1, "More than 1 player on the map!"));
		}
		i++;
	}
	if (i < 1)
		return (emsg(1, "Map contains empty line!"));
	return (0);
}

static int	read_first_map_line(t_re *re, char **line, t_list **tmpl)
{
	int		linelen;

	if (map_line_err(*line))
	{
		free(*line);
		return (emsg(-1, "Map line problem!"));
	}
	re->map.map_width = -1;
	re->map.map_height = 1;
	linelen = ft_strlen(*line);
	if (re->map.map_width < linelen)
		re->map.map_width = linelen;
	*tmpl = ft_lstnew(*line);
	return (0);
}

static int	read_mid_map_line(t_re *re, char **line, t_list **tmpl)
{
	t_list	*tmpelem;
	int		linelen;

	if (map_line_err(*line))
	{
		free(*line);
		ft_lstclear(tmpl, free);
		return (emsg(-1, "Map line problem!"));
	}
	linelen = ft_strlen(*line);
	if (re->map.map_width < linelen)
		re->map.map_width = linelen;
	(re->map.map_height)++;
	tmpelem = ft_lstnew(*line);
	ft_lstadd_back(tmpl, tmpelem);
	return (0);
}

static int	read_last_map_line(t_re *re, char **line, t_list **tmpl)
{
	t_list	*tmpelem;
	int		linelen;

	if (map_line_err(*line))
	{
		free(*line);
		ft_lstclear(tmpl, free);
		return (emsg(-1, "Map line problem!"));
	}
	linelen = ft_strlen(*line);
	if (re->map.map_width < linelen)
		re->map.map_width = linelen;
	tmpelem = ft_lstnew(*line);
	ft_lstadd_back(tmpl, tmpelem);
	(re->map.map_height)++;
	return (0);
}

int	read_map_list(t_re *re, char **line, int fd, t_list **tmpl)
{
	int		gres;

	if (read_first_map_line(re, line, tmpl) < 0)
		return (-1);
	gres = get_next_line(fd, line);
	while (gres > 0)
	{
		if (read_mid_map_line(re, line, tmpl) < 0)
			return (-1);
		gres = get_next_line(fd, line);
	}
	if (gres < 0)
	{
		ft_lstclear(tmpl, free);
		return (emsg(-1, "Read line error!"));
	}
	if (read_last_map_line(re, line, tmpl) < 0)
		return (-1);
	return (0);
}
