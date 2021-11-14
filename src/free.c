#include "../include/cub3d.h"

void	map_free(t_map *map)
{
	if (map->no)
		free(map->no);
	if (map->so)
		free(map->so);
	if (map->we)
		free(map->we);
	if (map->ea)
		free(map->ea);
	if (map->s)
		free(map->s);
	while (map->map_height > 0)
	{
		free(map->m[map->map_height - 1]);
		map->map_height--;
	}
	free(map->m);
	map_init(map);
}

int	free_all(int ret, t_re *re)
{
	if (re->img.ptr != NULL)
		mlx_destroy_image(re->mlx.ptr, re->img.ptr);
	if (re->mlx.win != NULL)
		mlx_destroy_window(re->mlx.ptr, re->mlx.win);
	free_all_mem(&(re->mm));
	re = NULL;
	get_next_line(-42, NULL);
	return (ret);
}
