#include "../../include/cub3d.h"

static	int	parse_color_part(char **line, unsigned char *c, int part)
{
	long	tmp;
	char	*last_position;

	while (**line == ' ')
		(*line)++;
	tmp = 0;
	last_position = *line;
	while (**line >= '0' && **line <= '9' && tmp <= 999)
	{
		tmp = tmp * 10 + **line - '0';
		(*line)++;
	}
	if (**line != ',' && part != 3)
		return (-1);
	if (last_position == *line)
		return (emsg(-1, "Incorrect RGB information!"));
	if (tmp > 255)
		return (emsg(-1, "Did you try to overflow me? :)"));
	*c = tmp;
	if (**line == ',' && part != 3)
		(*line)++;
	return (0);
}

static	int	parse_color_param(char *line, t_rgb *rgb)
{
	if (rgb->set != 0)
		return (emsg(-1, "Double define!"));
	rgb->set = 1;
	if (parse_color_part(&line, &(rgb->r), 1) < 0
		|| parse_color_part(&line, &(rgb->g), 2) < 0
		|| parse_color_part(&line, &(rgb->b), 3) < 0)
		return (emsg(-1, "Incorrect color format!"));
	while (*line == ' ')
		line++;
	if (*line != 0)
		return (emsg(-1, "Incorrect color format!"));
	return (1);
}

static	int	call_parse_worker_select(t_re *re, char *line)
{
	if (line[0] == 'R' && line[1] == ' ')
		return (parse_double_int_params(line + 2, &re->map));
	if (line[0] == 'S' && line[1] == ' ')
		return (parse_string_param(re, line + 2, &re->map.s));
	if (line[0] == 'N' && line[1] == 'O' && line[2] == ' ')
		return (parse_string_param(re, line + 3, &re->map.no));
	if (line[0] == 'S' && line[1] == 'O' && line[2] == ' ')
		return (parse_string_param(re, line + 3, &re->map.so));
	if (line[0] == 'W' && line[1] == 'E' && line[2] == ' ')
		return (parse_string_param(re, line + 3, &re->map.we));
	if (line[0] == 'E' && line[1] == 'A' && line[2] == ' ')
		return (parse_string_param(re, line + 3, &re->map.ea));
	if (line[0] == 'F' && line[1] == ' ')
		return (parse_color_param(line + 2, &re->map.f));
	if (line[0] == 'C' && line[1] == ' ')
		return (parse_color_param(line + 2, &re->map.c));
	return (-2);
}

int	call_parse_worker(t_re *re, char *line)
{
	int	len;
	int	res;

	len = ft_strlen(line);
	if (len == 0)
		return (0);
	res = call_parse_worker_select(re, line);
	if (res != -2)
		return (res);
	while (--len >= 0)
		if (ft_strchrpos(" 012NSEW", line[len]) < 0)
			return (emsg(-1, "Incorrect type identifier!"));
	return (emsg(-1, "Probably map starts before params defined!"));
}
