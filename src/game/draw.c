#include "../include/cub3d.h"

int	draw_sky(t_re *re)
{
	int	color;
	int	i;

	color = re->map.c.r * 256 * 256 + re->map.c.g * 256 + re->map.c.b;
	i = 0;
	while (i < re->map.ry / 2 * re->map.rx)
	{
		*(re->img.data + i) = color;
		i++;
	}
	color = re->map.f.r * 256 * 256 + re->map.f.g * 256 + re->map.f.b;
	i = re->map.ry / 2 * re->map.rx;
	while (i < re->map.ry * re->map.rx)
	{
		*(re->img.data + i) = color;
		i++;
	}
	return (0);
}

int	draw(t_re *re)
{
	player_move(re);
	draw_sky(re);
	draw_walls(re);
	sprites_start(re);
	mlx_put_image_to_window(re->mlx.ptr, re->mlx.win, re->img.ptr, 0, 0);
	return (0);
}
