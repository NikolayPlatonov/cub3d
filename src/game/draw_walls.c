#include "../../include/cub3d.h"

static void	wall_hit_loop(t_re *re, t_walls_calc *draw)
{
	int	hit;

	hit = 0;
	while (!hit)
	{
		if (draw->sided.x < draw->sided.y)
		{
			draw->sided.x += draw->delta_dist.x;
			draw->map.x += (int)draw->step.x;
			draw->side = 0;
		}
		else
		{
			draw->sided.y += draw->delta_dist.y;
			draw->map.y += (int)draw->step.y;
			draw->side = 1;
		}
		if (re->map.m[draw->map.x][draw->map.y] == '1')
			hit = 1;
	}
}

static void	wall_calc_nested(t_re *re, t_walls_calc *draw)
{
	if (!draw->side)
		draw->wall_distance = (draw->map.x - re->player_pos.x
				+ (1 - draw->step.x) / 2) / draw->rayd.x;
	else
		draw->wall_distance = (draw->map.y - re->player_pos.y
				+ (1 - draw->step.y) / 2) / draw->rayd.y;
	re->z_buffer[draw->x] = draw->wall_distance;
	draw->line_height = (int)(re->map.ry / draw->wall_distance
			* re->coefficient);
	draw->draw_start = re->map.ry / 2 - draw->line_height / 2;
	if (draw->draw_start < 0)
		draw->draw_start = 0;
	draw->draw_end = re->map.ry / 2 + draw->line_height / 2;
	if (draw->draw_end >= re->map.ry)
		draw->draw_end = re->map.ry;
}

static void	wall_x_and_texture(t_re *re, t_walls_calc *draw)
{
	if (draw->side == 1 && draw->rayd.y > 0)
		draw->tex_num = TEXTURE_WE;
	else if (draw->side == 1 && draw->rayd.y < 0)
		draw->tex_num = TEXTURE_EA;
	else if (draw->side == 0 && draw->rayd.x > 0)
		draw->tex_num = TEXTURE_SO;
	else
		draw->tex_num = TEXTURE_NO;
	if (draw->side == 0)
		draw->wall_x = re->player_pos.y + draw->wall_distance * draw->rayd.y;
	else
		draw->wall_x = re->player_pos.x + draw->wall_distance * draw->rayd.x;
	draw->wall_x -= floor(draw->wall_x);
	draw->tex.x = (int)(draw->wall_x
			* (double)re->texture[draw->tex_num].width);
	if (draw->side == 0 && draw->rayd.x > 0)
		draw->tex.x = re->texture[draw->tex_num].width - draw->tex.x - 1;
	if (draw->side == 1 && draw->rayd.y < 0)
		draw->tex.x = re->texture[draw->tex_num].width - draw->tex.x - 1;
}

static void	wall_draw_loop(t_re *re, t_walls_calc *draw)
{
	int	y;
	int	color;

	draw->ray_step = 1.0 * (double)re->texture[draw->tex_num].height
		/ (double)draw->line_height;
	draw->tex_pos = (draw->draw_start - (double)re->map.ry
			/ 2.0 + (double)draw->line_height / 2.0) * draw->ray_step;
	y = draw->draw_start;
	while (y < draw->draw_end)
	{
		draw->tex.y = (int)draw->tex_pos;
		draw->tex_pos += draw->ray_step;
		set_wall_color(re, draw, &color);
		*(re->img.data + y * re->map.rx + draw->x) = color;
		y++;
	}
}

int	draw_walls(t_re *re)
{
	t_walls_calc	draw;

	draw.x = 0;
	while (draw.x < re->map.rx)
	{
		wall_stripe_init(re, &draw);
		wall_step_set(re, &draw);
		wall_hit_loop(re, &draw);
		wall_calc_nested(re, &draw);
		wall_x_and_texture(re, &draw);
		wall_draw_loop(re, &draw);
		draw.x++;
	}
	return (0);
}
