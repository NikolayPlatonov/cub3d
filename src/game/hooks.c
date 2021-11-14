#include "cub3d.h"

int	window_close(t_re *re)
{
	free_all(0, re);
	exit(0);
}

int	key_down(int key, t_re *re)
{
	if (key == KEY_W)
		re->keys.w = 1;
	else if (key == KEY_S)
		re->keys.s = 1;
	else if (key == KEY_D)
		re->keys.d = 1;
	else if (key == KEY_A)
		re->keys.a = 1;
	else if (key == KEY_RIGHT)
		re->keys.ra = 1;
	else if (key == KEY_LEFT)
		re->keys.la = 1;
	else if (key == KEY_ESC)
	{
		free_all(0, re);
		exit(0);
	}
	return (0);
}

int	key_up(int key, t_re *re)
{
	if (key == KEY_W)
		re->keys.w = 0;
	else if (key == KEY_S)
		re->keys.s = 0;
	else if (key == KEY_D)
		re->keys.d = 0;
	else if (key == KEY_A)
		re->keys.a = 0;
	else if (key == KEY_RIGHT)
		re->keys.ra = 0;
	else if (key == KEY_LEFT)
		re->keys.la = 0;
	return (0);
}
