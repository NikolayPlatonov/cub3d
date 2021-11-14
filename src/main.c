#include "../include/cub3d.h"

static void	check_screen_size(t_re *re)
{
	t_ipoint	screen_size;

	mlx_get_screen_size(&screen_size.x, &screen_size.y);
	if (re->map.rx > screen_size.x)
		re->map.rx = screen_size.x;
	if (re->map.ry > screen_size.y)
		re->map.ry = screen_size.y;
}

int	main(int ac, char *av[])
{
	t_re	re;

	if (init_and_args_handle(&re, ac, av) < 0)
		return (-1);
	if (open_map(&re, av[1]) != 0)
		return (free_all(-1, &re));
	re.mlx.ptr = mlx_init();
	check_screen_size(&re);
	if (main_prep(&re) < 0)
		return (-1);
	if (re.save_flag)
	{
		if (screenshot(&re) < 0)
			return (-1);
		else
			return (0);
	}
	set_mlx_hooks(&re);
	mlx_loop(re.mlx.ptr);
	free_all(0, &re);
	return (0);
}
