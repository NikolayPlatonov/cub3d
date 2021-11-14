#include "../../include/cub3d.h"

void	wall_stripe_init(t_re *re, t_walls_calc *draw)
{
	draw->camv_x = 2 * draw->x / (double)re->map.rx - 1;
	draw->rayd.x = re->player_dir.x + re->plane.x * draw->camv_x;
	draw->rayd.y = re->player_dir.y + re->plane.y * draw->camv_x;
	draw->map.x = (int) re->player_pos.x;
	draw->map.y = (int) re->player_pos.y;
	draw->delta_dist.x = fabs(1 / draw->rayd.x);
	draw->delta_dist.y = fabs(1 / draw->rayd.y);
}

void	wall_step_set(t_re *re, t_walls_calc *draw)
{
	if (draw->rayd.x < 0)
	{
		draw->step.x = -1;
		draw->sided.x = (re->player_pos.x - draw->map.x)
			* draw->delta_dist.x;
	}
	else
	{
		draw->step.x = 1;
		draw->sided.x = (1.0 - re->player_pos.x + draw->map.x)
			* draw->delta_dist.x;
	}
	if (draw->rayd.y < 0)
	{
		draw->step.y = -1;
		draw->sided.y = (re->player_pos.y - draw->map.y)
			* draw->delta_dist.y;
	}
	else
	{
		draw->step.y = 1;
		draw->sided.y = (1.0 - re->player_pos.y + draw->map.y)
			* draw->delta_dist.y;
	}
}

void	set_wall_color(t_re *re, t_walls_calc *draw, int *color)
{
	if (draw->tex.y < 0)
		draw->tex.y = 0;
	else if (draw->tex.y >= re->texture[draw->tex_num].height)
		draw->tex.y = re->texture[draw->tex_num].height - 1;
	if (draw->tex.x < 0)
		draw->tex.x = 0;
	else if (draw->tex.x >= re->texture[draw->tex_num].width)
		draw->tex.x = re->texture[draw->tex_num].width - 1;
	*color = re->texture[draw->tex_num].data[re->texture[
		draw->tex_num].width * draw->tex.y + draw->tex.x];
	*color = *color & 0xFFFFFF;
	if (draw->side == 1)
		*color = (*color >> 1) & 8355711;
}
