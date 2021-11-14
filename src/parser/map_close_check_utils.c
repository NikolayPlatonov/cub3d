#include "../../include/cub3d.h"

void	map_decode(t_re *re)
{
	int	i;
	int	j;

	i = -1;
	while (++i < re->map.map_height)
	{
		j = -1;
		while (++j < re->map.map_width)
		{
			if (re->map.m[i][j] == 'a')
				re->map.m[i][j] = '0';
			else if (re->map.m[i][j] == 'b')
				re->map.m[i][j] = '1';
			else if (re->map.m[i][j] == 'c')
				re->map.m[i][j] = '2';
		}
	}
}

int	is_map_break(t_re *re, int x, int y)
{
	if (x < 0 || y < 0 || x >= re->map.map_width || y >= re->map.map_height)
		return (1);
	return (0);
}
