#ifndef CUB3D_H
# define CUB3D_H
# include <fcntl.h>
# include <math.h>
# include "../mlx/mlx.h"
# include "../libft/src/libft.h"

# define MAX_INT 2147483647
# define KEY_W 13
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_LEFT 123
# define KEY_RIGHT 124
# define KEY_ESC 53
# define TEXTURE_NO 0
# define TEXTURE_SO 1
# define TEXTURE_WE 2
# define TEXTURE_EA 3
# define TEXTURE_S 4

typedef struct s_keys
{
	int	w;
	int	a;
	int	s;
	int	d;
	int	la;
	int	ra;
}	t_keys;

typedef struct s_rgb
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
	unsigned char	set;
}	t_rgb;

typedef struct s_dpoint
{
	double	x;
	double	y;
}	t_dpoint;

typedef struct s_ipoint
{
	int	x;
	int	y;
}	t_ipoint;

typedef struct s_sprite
{
	t_dpoint	position;
	double		distance;
	t_dpoint	relative_position;
}	t_sprite;

typedef struct s_sprite_calc
{
	double		inverse_determinant;
	t_dpoint	transform;
	int			sprite_screen_x;
	int			sprite_height;
	t_ipoint	draw_start;
	t_ipoint	draw_end;
	int			sprite_width;
	int			stripe;
	t_dpoint	texture;
	int			color;
	double		d;
	int			y;
}	t_sprite_calc;

typedef struct s_walls_calc
{
	int			x;
	double		camv_x;
	t_ipoint	map;
	t_dpoint	rayd;
	t_dpoint	sided;
	t_dpoint	delta_dist;
	double		wall_distance;
	t_dpoint	step;
	int			side;
	int			line_height;
	int			draw_start;
	int			draw_end;
	int			tex_num;
	double		wall_x;
	t_ipoint	tex;
	double		ray_step;
	double		tex_pos;
}	t_walls_calc;

typedef struct s_map
{
	int		rx;
	int		ry;
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	char	*s;
	t_rgb	f;
	t_rgb	c;
	char	**m;
	int		map_width;
	int		map_height;
}	t_map;

typedef struct s_img
{
	void		*ptr;
	int			*data;
	int			size_l;
	int			bpp;
	int			endian;
	int			width;
	int			height;
}	t_img;

typedef struct s_mlx
{
	void	*ptr;
	void	*win;
}	t_mlx;

typedef struct s_texture
{
	int	height;
	int	width;
	int	*data;
}	t_texture;

typedef struct s_mem_node
{
	struct s_mem_node	*prev;
	struct s_mem_node	*next;
	void				*data;
}	t_mem_node;

typedef struct s_re
{
	t_map		map;
	t_mlx		mlx;
	t_img		img;
	t_mem_node	*mm;
	t_dpoint	player_pos;
	t_dpoint	player_dir;
	t_dpoint	plane;
	t_texture	texture[5];
	double		move_speed;
	double		rotation_speed;
	t_sprite	**sprites;
	int			sprites_count;
	double		*z_buffer;
	t_keys		keys;
	double		coefficient;
	int			save_flag;
}	t_re;

int			emsg(int ret, const char *msg);
int			open_map(t_re *re, char *path);
int			map_close_check(t_re *re);
void		map_decode(t_re *re);
int			is_map_break(t_re *re, int x, int y);
int			locate_sprites(t_re *re);
int			locate_player(t_re *re);
int			check_map_path(char *path);
int			check_all_textures_path(t_re *re);
void		player_move(t_re *re);
void		rotate_right(t_re *re);
void		rotate_left(t_re *re);
t_mem_node	*new_mem(t_mem_node **first, size_t size);
t_mem_node	*new_mem_assign(t_mem_node **first, void **ptr, size_t size);
void		*free_mem(t_mem_node **first, t_mem_node **mem_obj);
void		*free_mem_by_ptr(t_mem_node **first, void **ptr);
void		free_all_mem(t_mem_node **first);
void		*add_mem_by_ptr(t_mem_node **first, void *ptr);
int			window_close(t_re *re);
int			key_down(int key, t_re *re);
int			key_up(int key, t_re *re);
int			free_all(int ret, t_re *re);
int			load_all_textures(t_re *re);
int			draw(t_re *re);
int			draw_walls(t_re *re);
int			draw_sky(t_re *re);
void		wall_stripe_init(t_re *re, t_walls_calc *draw);
void		wall_step_set(t_re *re, t_walls_calc *draw);
void		set_wall_color(t_re *re, t_walls_calc *draw, int *color);
void		sprites_start(t_re *re);
int			parse_double_int_params(char *line, t_map *map);
int			parse_string_param(t_re *re, char *line, char **str);
int			call_parse_worker(t_re *re, char *line);
void		sort_sprites(t_sprite **sprites, int count);
int			read_param_line_worker(t_re *re, char **line, int *fields_found);
int			read_params(t_re *re, int fd);
int			read_empty_lines(int fd, char **line);
int			read_map_list(t_re *re, char **line, int fd, t_list **tmpl);
int			map_close_check_2(t_re *re);
void		init_all(t_re *re);
void		map_init(t_map *map);
int			screenshot(t_re *re);
int			init_and_args_handle(t_re *re, int ac, char *av[]);
void		set_mlx_hooks(t_re *re);
int			main_prep(t_re *re);

#endif
