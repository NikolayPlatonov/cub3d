#include "../../include/cub3d.h"

static int	locate_sprites_nested(t_re *re)
{
	int	i;
	int	j;
	int	k;

	if (!(new_mem_assign(&re->mm, (void **) &re->sprites,
				re->sprites_count * sizeof(t_sprite *))))
		return (emsg(-1, "Malloc (t_sprite*) error!"));
	i = -1;
	k = 0;
	while (++i < re->map.map_height)
	{
		j = -1;
		while (++j < re->map.map_width)
		{
			if (re->map.m[i][j] == '2')
			{
				if (!(new_mem_assign(&re->mm, (void **) &re->sprites[k],
							sizeof(t_sprite))))
					return (emsg(-1, "Malloc (t_sprite) error!"));
				re->sprites[k]->position.x = i + 0.5;
				re->sprites[k++]->position.y = j + 0.5;
			}
		}
	}
	return (0);
}

int	locate_sprites(t_re *re)
{
	int	i;
	int	j;

	i = -1;
	while (++i < re->map.map_height)
	{
		j = -1;
		while (++j < re->map.map_width)
			if (re->map.m[i][j] == '2')
				re->sprites_count++;
	}
	if (re->sprites_count > 0)
	{
		if (locate_sprites_nested(re) < 0)
			return (-1);
	}
	return (0);
}
