#include "../../include/cub3d.h"

void	rotate_right(t_re *re)
{
	double	old_direction_x;
	double	old_plane_x;

	old_direction_x = re->player_dir.x;
	re->player_dir.x = re->player_dir.x * cos(-re->rotation_speed)
		- re->player_dir.y * sin(-re->rotation_speed);
	re->player_dir.y = old_direction_x * sin(-re->rotation_speed)
		+ re->player_dir.y * cos(-re->rotation_speed);
	old_plane_x = re->plane.x;
	re->plane.x = re->plane.x * cos(-re->rotation_speed)
		- re->plane.y * sin(-re->rotation_speed);
	re->plane.y = old_plane_x * sin(-re->rotation_speed)
		+ re->plane.y * cos(-re->rotation_speed);
}

void	rotate_left(t_re *re)
{
	double	old_direction_x;
	double	old_plane_x;

	old_direction_x = re->player_dir.x;
	re->player_dir.x = re->player_dir.x * cos(re->rotation_speed)
		- re->player_dir.y * sin(re->rotation_speed);
	re->player_dir.y = old_direction_x * sin(re->rotation_speed)
		+ re->player_dir.y * cos(re->rotation_speed);
	old_plane_x = re->plane.x;
	re->plane.x = re->plane.x * cos(re->rotation_speed)
		- re->plane.y * sin(re->rotation_speed);
	re->plane.y = old_plane_x * sin(re->rotation_speed)
		+ re->plane.y * cos(re->rotation_speed);
}
