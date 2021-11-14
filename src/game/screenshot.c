#include "../include/cub3d.h"

static char	*bmp_init(t_re *re)
{
	char	*bitmap;
	int		size;

	size = re->map.rx * re->map.ry * 4 + 54;
	bitmap = malloc(sizeof(char) * 54);
	if (!bitmap)
		return (NULL);
	ft_bzero(bitmap, 54);
	bitmap[0] = 'B';
	bitmap[1] = 'M';
	bitmap[2] = size;
	bitmap[3] = size >> 8;
	bitmap[4] = size >> 16;
	bitmap[5] = size >> 24;
	*(int *)(bitmap + 10) = 54;
	*(int *)(bitmap + 14) = 40;
	*(int *)(bitmap + 18) = re->map.rx;
	*(int *)(bitmap + 22) = re->map.ry;
	*(bitmap + 26) = 1;
	*(bitmap + 28) = 32;
	return (bitmap);
}

static void	write_data(int fd, t_re *re)
{
	int	y;
	int	x;
	int	color;

	y = re->map.ry - 1;
	while (y >= 0)
	{
		x = 0;
		while (x < re->map.rx)
		{
			color = *((int *)re->img.data + y * re->map.rx + x);
			write(fd, &color, 4);
			x++;
		}
		y--;
	}
}

int	screenshot(t_re *re)
{
	int		fd;
	char	*bitmap;

	draw_sky(re);
	draw_walls(re);
	sprites_start(re);
	fd = open("screenshot.bmp", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
	if (fd < 0)
	{
		emsg(-1, "Сan't create file!");
		return (free_all(-1, re));
	}
	bitmap = bmp_init(re);
	write(fd, bitmap, 54);
	free(bitmap);
	write_data(fd, re);
	close(fd);
	return (free_all(0, re));
}
