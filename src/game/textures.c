#include "cub3d.h"

static void	load_texture_nested(t_re *re, int texture_id, t_img	*img)
{
	int		y;
	int		x;

	y = -1;
	while (++y < img->height)
	{
		x = -1;
		while (++x < img->width)
			re->texture[texture_id].data[img->width * y + x]
				= img->data[img->width * y + x];
	}
}

int	load_texture(t_re *re, int texture_id, char **path)
{
	t_img	*img;

	if (!(new_mem_assign(&re->mm, (void **)&img, sizeof(t_img))))
		return (emsg(0, "Cannot allocate memory!"));
	img->ptr = mlx_xpm_file_to_image(re->mlx.ptr, *path,
			&img->width, &img->height);
	if (!img->ptr)
		return (emsg(0, "Cannot open texture!"));
	img->data = (int *)mlx_get_data_addr(img->ptr, &img->bpp,
			&img->size_l, &img->endian);
	re->texture[texture_id].height = img->height;
	re->texture[texture_id].width = img->width;
	if (!(new_mem_assign(&re->mm, (void **)&re->texture[texture_id].data,
				img->width * img->height * sizeof(int))))
		return (emsg(0, "Cannot allocate memory!"));
	load_texture_nested(re, texture_id, img);
	mlx_destroy_image(re->mlx.ptr, img->ptr);
	free_mem_by_ptr(&re->mm, (void **)&img);
	return (1);
}

int	load_all_textures(t_re *re)
{
	int	i;

	i = 0;
	while (i < 5)
	{
		re->texture[i].data = NULL;
		re->texture[i].height = 0;
		re->texture[i].width = 0;
		i++;
	}
	if (!load_texture(re, TEXTURE_NO, &re->map.no))
		return (0);
	if (!load_texture(re, TEXTURE_SO, &re->map.so))
		return (0);
	if (!load_texture(re, TEXTURE_WE, &re->map.we))
		return (0);
	if (!load_texture(re, TEXTURE_EA, &re->map.ea))
		return (0);
	if (!load_texture(re, TEXTURE_S, &re->map.s))
		return (0);
	return (1);
}
