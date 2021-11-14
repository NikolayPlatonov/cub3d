#include "../../include/cub3d.h"

static	void	move_forward(t_re *re)
{
	if (re->map.m[(int)(re->player_pos.x + re->player_dir.x
			* re->move_speed)][(int)(re->player_pos.y)] != '1')
		re->player_pos.x += re->player_dir.x * re->move_speed;
	if (re->map.m[(int)(re->player_pos.x)][(int)(re->player_pos.y
			+ re->player_dir.y * re->move_speed)] != '1')
		re->player_pos.y += re->player_dir.y * re->move_speed;
}

static	void	move_backward(t_re *re)
{
	if (re->map.m[(int)(re->player_pos.x - re->player_dir.x
			* re->move_speed)][(int)(re->player_pos.y)] != '1')
		re->player_pos.x -= re->player_dir.x * re->move_speed;
	if (re->map.m[(int)(re->player_pos.x)][(int)(re->player_pos.y
			- re->player_dir.y * re->move_speed)] != '1')
		re->player_pos.y -= re->player_dir.y * re->move_speed;
}

static	void	move_right(t_re *re)
{
	if (re->map.m[(int)(re->player_pos.x + re->player_dir.y
			* re->move_speed)][(int)(re->player_pos.y)] != '1')
		re->player_pos.x += re->player_dir.y * re->move_speed;
	if (re->map.m[(int)(re->player_pos.x)][(int)(re->player_pos.y
			- re->player_dir.x * re->move_speed)] != '1')
		re->player_pos.y -= re->player_dir.x * re->move_speed;
}

static	void	move_left(t_re *re)
{
	if (re->map.m[(int)(re->player_pos.x - re->player_dir.y
			* re->move_speed)][(int)(re->player_pos.y)] != '1')
		re->player_pos.x -= re->player_dir.y * re->move_speed;
	if (re->map.m[(int)(re->player_pos.x)][(int)(re->player_pos.y
			+ re->player_dir.x * re->move_speed)] != '1')
		re->player_pos.y += re->player_dir.x * re->move_speed;
}

void	player_move(t_re *re)
{
	if (re->keys.w && !re->keys.s)
		move_forward(re);
	else if (re->keys.s && !re->keys.w)
		move_backward(re);
	if (re->keys.a && !re->keys.d)
		move_left(re);
	else if (re->keys.d && !re->keys.a)
		move_right(re);
	if (re->keys.la && !re->keys.ra)
		rotate_left(re);
	else if (re->keys.ra && !re->keys.la)
		rotate_right(re);
}
