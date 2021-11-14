#include "../../include/cub3d.h"

static int	map_check_position_nested(t_re *re, int x, int y)
{
	int	i;
	int	wall_found;

	i = 0;
	wall_found = 0;
	while (!wall_found && y + (++i) < re->map.map_height
		   && re->map.m[y + i][x] != ' ')
		if (re->map.m[y + i][x] == '1')
			wall_found = 1;
	if (!wall_found)
		return (-1);
	i = 0;
	wall_found = 0;
	while (!wall_found && y - (++i) >= 0
		   && re->map.m[y - i][x] != ' ')
		if (re->map.m[y - i][x] == '1')
			wall_found = 1;
	if (!wall_found)
		return (-1);
	return (0);
}

static int	map_check_position(t_re *re, int x, int y)
{
	int	i;
	int	wall_found;

	i = 0;
	wall_found = 0;
	while (!wall_found && x + (++i) < re->map.map_width
		&& re->map.m[y][x + i] != ' ')
		if (re->map.m[y][x + i] == '1')
			wall_found = 1;
	if (!wall_found)
		return (-1);
	i = 0;
	wall_found = 0;
	while (!wall_found && x - (++i) >= 0
		&& re->map.m[y][x - i] != ' ')
		if (re->map.m[y][x - i] == '1')
			wall_found = 1;
	if (!wall_found)
		return (-1);
	if (map_check_position_nested(re, x, y) < 0)
		return (-1);
	return (0);
}

int	map_close_check_2(t_re *re)
{
	int	x;
	int	y;

	y = -1;
	while (++y < re->map.map_height)
	{
		x = -1;
		while (++x < re->map.map_width)
		{
			if (ft_strchr("02NSWE", re->map.m[y][x])
				&& map_check_position(re, x, y) < 0)
				return (-1);
		}
	}
	return (0);
}
