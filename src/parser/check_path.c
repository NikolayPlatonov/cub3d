#include "../../include/cub3d.h"

int	check_map_path(char *path)
{
	int	plen;

	plen = ft_strlen(path);
	if (plen < 4 || path[plen - 1] != 'b' || path[plen - 2] != 'u'
		|| path[plen - 3] != 'c' || path[plen - 4] != '.')
		return (emsg(-1, "Incorrect map name!"));
	return (0);
}

static	int	check_texture_path(char *path)
{
	int		plen;

	plen = ft_strlen(path);
	if (plen < 4 || path[plen - 1] != 'm' || path[plen - 2] != 'p'
		|| path[plen - 3] != 'x' || path[plen - 4] != '.')
		return (emsg(-1, "Incorrect texture file! (.xmp expected)"));
	return (0);
}

int	check_all_textures_path(t_re *re)
{
	if (check_texture_path(re->map.no) < 0
		|| check_texture_path(re->map.so) < 0
		|| check_texture_path(re->map.we) < 0
		|| check_texture_path(re->map.ea) < 0
		|| check_texture_path(re->map.s) < 0)
		return (-1);
	return (0);
}
