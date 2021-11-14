#include "../include/cub3d.h"

int	read_param_line_worker(t_re *re, char **line, int *fields_found)
{
	int	tmp;

	tmp = call_parse_worker(re, *line);
	if (tmp < 0)
	{
		free(*line);
		return (emsg(-1, "Param line problem!"));
	}
	*fields_found += tmp;
	free(*line);
	return (0);
}

static int	read_params_error_handler(int gres, char **line, int fields_found)
{
	if (gres < 0)
	{
		if (*line != NULL)
			free(*line);
		return (emsg(-1, "Read line error!"));
	}
	if (fields_found < 8 || gres == 0)
	{
		if (*line != NULL)
			free(*line);
		return (emsg(-1, "Map is not complete!"));
	}
	return (0);
}

int	read_params(t_re *re, int fd)
{
	char	*line;
	int		gres;
	int		fields_found;

	fields_found = 0;
	line = NULL;
	gres = get_next_line(fd, &line);
	while (fields_found < 8 && gres > 0)
	{
		if (read_param_line_worker(re, &line, &fields_found) < 0)
			return (-1);
		if (fields_found < 8)
		{
			line = NULL;
			gres = get_next_line(fd, &line);
		}
	}
	if (read_params_error_handler(gres, &line, fields_found) < 0)
		return (-1);
	return (0);
}

int	read_empty_lines(int fd, char **line)
{
	int		gres;

	gres = get_next_line(fd, line);
	while (gres == 1 && ft_strlen(*line) == 0)
	{
		free(*line);
		gres = get_next_line(fd, line);
	}
	if (gres < 0)
	{
		free(*line);
		return (emsg(-1, "Read line error!"));
	}
	if (gres == 0)
	{
		free(*line);
		return (emsg(-1, "Map is not complete!"));
	}
	return (0);
}
