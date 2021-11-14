#include "cub3d.h"

void	sort_sprites(t_sprite **sprites, int count)
{
	int			i;
	int			j;
	int			flag_sorted;
	t_sprite	*tmp;

	i = count - 1;
	while (i >= 0)
	{
		j = 0;
		flag_sorted = 1;
		while (j < i)
		{
			if (sprites[j]->distance < sprites[j + 1]->distance)
			{
				tmp = sprites[j];
				sprites[j] = sprites[j + 1];
				sprites[j + 1] = tmp;
				flag_sorted = 0;
			}
			j++;
		}
		if (flag_sorted)
			break ;
		i--;
	}
}
