#include "../../include/cub3d.h"

static	void	set_player_direction(t_re *re, int i, int j)
{
	if (re->map.m[i][j] == 'N')
	{
		re->player_dir.x = -1;
		re->player_dir.y = 0;
	}
	else if (re->map.m[i][j] == 'S')
	{
		re->player_dir.x = 1;
		re->player_dir.y = 0;
	}
	else if (re->map.m[i][j] == 'W')
	{
		re->player_dir.x = 0;
		re->player_dir.y = -1;
	}
	else if (re->map.m[i][j] == 'E')
	{
		re->player_dir.x = 0;
		re->player_dir.y = 1;
	}
}

static	int	set_player_position(t_re *re, int i, int j, int *k)
{
	if (*k != 0)
		return (emsg(-1, "More than 1 player on map!"));
	*k = 1;
	re->player_pos.x = i + 0.500001;
	re->player_pos.y = j + 0.500001;
	re->plane.x = 0.66 * re->player_dir.y;
	re->plane.y = -0.66 * re->player_dir.x;
	return (0);
}

int	locate_player(t_re *re)
{
	int	i;
	int	j;
	int	k;

	k = 0;
	i = -1;
	while (++i < re->map.map_height)
	{
		j = -1;
		while (++j < re->map.map_width)
		{
			set_player_direction(re, i, j);
			if (ft_strchrpos("NSEW", re->map.m[i][j]) >= 0)
				if (set_player_position(re, i, j, &k) < 0)
					return (-1);
		}
	}
	if (k < 1)
		return (emsg(-1, "No player on map!"));
	return (0);
}
