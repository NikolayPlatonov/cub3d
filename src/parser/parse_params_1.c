#include "../../include/cub3d.h"

static	int	parse_double_int_params_second(char *line, t_map *map)
{
	long	tmp;

	tmp = 0;
	while (*line >= '0' && *line <= '9' && tmp < (long)MAX_INT)
	{
		tmp = tmp * 10 + *line - '0';
		line++;
	}
	if ((*line >= '0' && *line <= '9') || tmp > (long)MAX_INT)
		tmp = MAX_INT;
	while (*line >= '0' && *line <= '9')
		line++;
	map->ry = (int)tmp;
	while (*line == ' ')
		line++;
	if (*line != '\0')
		return (emsg(-1, "Incorrect resolution format!"));
	if (map->rx < 1 || map->ry < 1)
		return (emsg(-1, "Resolution can't be less than 1!"));
	if (map->rx < 100 || map->ry < 100)
		return (emsg(-1, "Resolution is TOO low. Do you have a microscope?"));
	return (1);
}

int	parse_double_int_params(char *line, t_map *map)
{
	long	tmp;

	if (map->rx != 0 || map->ry != 0)
		return (emsg(-1, "Double define!"));
	while (*line == ' ')
		line++;
	tmp = 0;
	while (*line >= '0' && *line <= '9' && tmp < (long)MAX_INT)
	{
		tmp = tmp * 10 + *line - '0';
		line++;
	}
	if ((*line >= '0' && *line <= '9') || tmp > (long)MAX_INT)
		tmp = MAX_INT;
	while (*line >= '0' && *line <= '9')
		line++;
	map->rx = (int)tmp;
	while (*line == ' ')
		line++;
	if (parse_double_int_params_second(line, map) < 0)
		return (-1);
	return (1);
}

int	parse_string_param(t_re *re, char *line, char **str)
{
	char	*end;

	if (*str != NULL)
		return (emsg(-1, "Double define!"));
	while (*line == ' ')
		line++;
	end = line;
	while (*end)
		end++;
	while (end > line && *(end - 1) == ' ')
		end--;
	if (end <= line)
		return (emsg(-1, "Empty path!"));
	if (!(new_mem_assign(&re->mm, (void **)str, (int)(end - line + 1))))
		return (emsg(-1, "Malloc error!"));
	ft_memmove(*str, line, end - line);
	*((*str) + (int)(end - line)) = '\0';
	return (1);
}
