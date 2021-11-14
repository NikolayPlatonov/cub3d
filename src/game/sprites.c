#include "cub3d.h"

static	void	sprites_calc_draw_loop_nested(t_re *re, t_sprite_calc	*sprite)
{
	sprite->d = sprite->y * 256 - re->map.ry * 128
		+ sprite->sprite_height * 128;
	sprite->texture.y = ((sprite->d * re->texture[TEXTURE_S].height)
			/ sprite->sprite_height) / 256;
	if (sprite->texture.y < 0)
		sprite->texture.y = 0;
	if (sprite->texture.y >= re->texture[TEXTURE_S].height)
		sprite->texture.y = re->texture[TEXTURE_S].height - 1;
	sprite->color = re->texture[TEXTURE_S].data[re->texture[TEXTURE_S].width
		* (int)sprite->texture.y + (int)sprite->texture.x];
	if (sprite->color != re->texture[TEXTURE_S].data[0])
		*(re->img.data + (sprite->y + 0) * re->map.rx + sprite->stripe)
			= sprite->color;
}

static void	sprites_calc_draw_loop(t_re *re, t_sprite_calc	*sprite)
{
	sprite->stripe = sprite->draw_start.x - 1;
	while (++sprite->stripe < sprite->draw_end.x)
	{
		sprite->texture.x = ((256 * (sprite->stripe
						- (sprite->sprite_screen_x
							- sprite->sprite_width / 2.0))
					* re->texture[TEXTURE_S].width
					/ sprite->sprite_width) / 256);
		if (sprite->transform.y > 0 && sprite->stripe >= 0
			&& sprite->stripe < re->map.rx
			&& sprite->transform.y < re->z_buffer[sprite->stripe])
		{
			sprite->y = sprite->draw_start.y - 1;
			while (++sprite->y <= sprite->draw_end.y)
				sprites_calc_draw_loop_nested(re, sprite);
		}
	}
}

static void	sprites_calc_prep(t_re *re, t_sprite_calc	*sprite)
{
	sprite->sprite_screen_x = (int)((re->map.rx / 2)
			* (1 + sprite->transform.x / sprite->transform.y));
	sprite->sprite_height = (int)fabs(re->map.ry
			/ sprite->transform.y * re->coefficient);
	sprite->draw_start.y = re->map.ry / 2 - sprite->sprite_height / 2;
	if (sprite->draw_start.y < 0)
		sprite->draw_start.y = 0;
	sprite->draw_end.y = re->map.ry / 2 + sprite->sprite_height / 2;
	if (sprite->draw_end.y >= re->map.ry)
		sprite->draw_end.y = re->map.ry - 1;
	sprite->sprite_width = (int)fabs(re->map.ry
			/ sprite->transform.y * re->coefficient);
	sprite->draw_start.x = sprite->sprite_screen_x - sprite->sprite_width / 2;
	if (sprite->draw_start.x < 0)
		sprite->draw_start.x = 0;
	sprite->draw_end.x = sprite->sprite_width / 2 + sprite->sprite_screen_x;
	if (sprite->draw_end.x > re->map.rx)
		sprite->draw_end.x = re->map.rx;
}

static void	sprites_calc(t_re *re)
{
	int				i;
	t_sprite_calc	sprite;

	sprite.inverse_determinant = 1.0 / (re->plane.x * re->player_dir.y
			- re->player_dir.x * re->plane.y);
	i = 0;
	while (i < re->sprites_count)
	{
		sprite.transform.x = sprite.inverse_determinant
			* (re->player_dir.y * re->sprites[i]->relative_position.x
				- re->player_dir.x * re->sprites[i]->relative_position.y);
		sprite.transform.y = sprite.inverse_determinant
			* (-re->plane.y * re->sprites[i]->relative_position.x
				+ re->plane.x * re->sprites[i]->relative_position.y);
		if (sprite.transform.y > 0)
		{
			sprites_calc_prep(re, &sprite);
			sprites_calc_draw_loop(re, &sprite);
		}
		i++;
	}
}

void	sprites_start(t_re *re)
{
	int	i;

	if (re->sprites_count < 1)
		return ;
	i = 0;
	while (i < re->sprites_count)
	{
		re->sprites[i]->distance
			= (re->player_pos.x - re->sprites[i]->position.x)
			* (re->player_pos.x - re->sprites[i]->position.x)
			+ (re->player_pos.y - re->sprites[i]->position.y)
			* (re->player_pos.y - re->sprites[i]->position.y);
		re->sprites[i]->relative_position.x
			= re->sprites[i]->position.x - re->player_pos.x;
		re->sprites[i]->relative_position.y
			= re->sprites[i]->position.y - re->player_pos.y;
		i++;
	}
	sort_sprites(re->sprites, re->sprites_count);
	sprites_calc(re);
}
