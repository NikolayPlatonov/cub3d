#include "../include/cub3d.h"

static int	is_save(const char *str)
{
	if (str[0] == '-'
		&& str[1] == '-'
		&& str[2] == 's'
		&& str[3] == 'a'
		&& str[4] == 'v'
		&& str[5] == 'e'
		&& str[6] == 0)
		return (1);
	return (0);
}

int	init_and_args_handle(t_re *re, int ac, char *av[])
{
	init_all(re);
	if (ac < 2 || ac > 3)
		return (emsg(-1, "Incorrect arguments count!"));
	if (ac == 3)
	{
		if (is_save(av[2]))
			re->save_flag = 1;
		else
			return (emsg(-1, "Incorrect arguments!"));
	}
	return (0);
}

void	set_mlx_hooks(t_re *re)
{
	mlx_do_key_autorepeatoff(re->mlx.ptr);
	mlx_hook(re->mlx.win, 17, 1L << 17, &window_close, re);
	mlx_hook(re->mlx.win, 2, 1L << 0, &key_down, re);
	mlx_hook(re->mlx.win, 3, 1L << 1, &key_up, re);
	mlx_loop_hook (re->mlx.ptr, &draw, re);
}

int	main_prep(t_re *re)
{
	re->coefficient = (double)re->map.rx / (double)re->map.ry / 16 * 9;
	if (!re->save_flag)
		re->mlx.win = mlx_new_window(re->mlx.ptr,
				re->map.rx, re->map.ry, "cub3D");
	if (!load_all_textures(re))
		return (free_all(-1, re));
	if (!new_mem_assign(&re->mm, (void **)&re->z_buffer,
			sizeof(double) * re->map.rx))
		return (free_all(emsg(-1, "Memory allocation error!"), re));
	re->img.ptr = mlx_new_image(re->mlx.ptr, re->map.rx, re->map.ry);
	re->img.data = (int *)mlx_get_data_addr(re->img.ptr,
			&re->img.bpp, &re->img.size_l, &re->img.endian);
	return (0);
}
