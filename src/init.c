#include "../include/cub3d.h"

void	map_init(t_map *map)
{
	map->rx = 0;
	map->ry = 0;
	map->no = NULL;
	map->so = NULL;
	map->we = NULL;
	map->ea = NULL;
	map->s = NULL;
	map->f.r = 0;
	map->f.g = 0;
	map->f.b = 0;
	map->f.set = 0;
	map->c.r = 0;
	map->c.g = 0;
	map->c.b = 0;
	map->c.set = 0;
	map->m = NULL;
	map->map_width = -1;
	map->map_height = 0;
}

void	init_all(t_re *re)
{
	re->mm = NULL;
	re->sprites = NULL;
	re->sprites_count = 0;
	re->mlx.ptr = NULL;
	re->mlx.win = NULL;
	re->img.ptr = NULL;
	re->img.data = NULL;
	re->keys.w = 0;
	re->keys.a = 0;
	re->keys.s = 0;
	re->keys.d = 0;
	re->keys.la = 0;
	re->keys.ra = 0;
	re->save_flag = 0;
	map_init(&re->map);
	re->move_speed = 0.031;
	re->rotation_speed = 0.03;
}
