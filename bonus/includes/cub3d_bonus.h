/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vluo <vluo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 13:23:04 by vluo              #+#    #+#             */
/*   Updated: 2025/06/11 16:15:49 by vluo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# include "../../libft/includes/libft.h"
# include "../../libft/includes/get_next_line_bonus.h"
# include "../../minilibx-linux/mlx.h"
# include <unistd.h>
# include <stdlib.h>
# include <X11/keysym.h>
# include <stdio.h>
# include <math.h>
# include <fcntl.h>

# define PI 3.14159265358979323846
# define DRAD 0.0174533

# define RES_X 960
# define RES_Y 640
# define CELLSIZE 64

// CALLOC USED

typedef struct s_array
{
	int		tot_len;
	int		arr_i;
	char	**arr;
}	t_array;

typedef struct s_xpm
{
	int	height;
	int	width;
	int	nb_char;
	int	char_length;
	int	**arr;
}	t_xpm;

typedef struct s_pos
{
	float	x;
	float	y;
}	t_pos;

typedef struct s_player
{
	t_pos	*pos;
	t_pos	*d;
	float	a;
}	t_player;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		b_p_p;
	int		lin_len;
	int		endian;
}	t_img;

typedef struct s_ray
{
	float	hline;
	t_pos	minhdist;
	t_pos	minvdist;
	t_pos	mindist;
	t_img	*tex;
	float	tx;
	float	ty_off;
	float	ty_step;
}	t_ray;

typedef struct s_data
{
	void		*mlx;
	void		*win;
	t_img		*img;
	t_player	*p;
	int			**map;
	t_img		*no;
	t_img		*so;
	t_img		*we;
	t_img		*ea;
	t_img		*door;
	t_img		*door_open;
	int			floor_col;
	int			ceiling_col;
	t_img		*minimap;
	int			frame;
}	t_data;

void		free_data(t_data *data);
t_img		*init_img(t_data *data, void *img_ptr, int res_x, int res_y);
t_player	*init_player(t_pos *pos_init, float angle_init);

t_pos		*init_pos(float x, float y);
void		asign_pos(t_pos *pos, float x, float y);
float		dist(t_pos *a, t_pos *b);
float		limit_angle(float nb);
int			trgb(int t, int r, int g, int b);
int			hex_to_dec(char *nb);
void		free_tab(char **tab);
void		get_dir_texture(t_ray *ray, t_pos r, t_data *data, int dir);

int			**init_map(void);
void		drawmap2d(t_data *data);

void		put_pixel(t_img *img, t_pos *a, int color, int do_free);
void		drawline(t_img *img, t_pos *a, t_pos *b, int color);
void		draw_straight(t_img	*img, t_pos	*a, t_pos *b, int color);

void		get_hray(float ra, t_pos *hray, t_data *data);
void		get_vray(float ra, t_pos *vray, t_data *data);
void		drawrays(t_data *data);

int			display(t_data *data);
int			close_win(t_data *data);
int			handle_key_input(int keysym, t_data *data);
void		handle_wasd(int keysym, t_data *data);
int			handle_mouse(int x, int y, t_data *data);

#endif