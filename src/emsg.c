#include "cub3d.h"

int	emsg(int ret, const char *msg)
{
	int			len;
	static int	flag;

	len = ft_strlen(msg);
	if (!flag)
		write(1, "Error\n", 6);
	if (len > 0)
	{
		write(1, msg, len);
		write(1, "\n", 1);
	}
	flag = 1;
	return (ret);
}
