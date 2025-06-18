/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vluo <vluo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 13:23:04 by vluo              #+#    #+#             */
/*   Updated: 2025/06/17 13:53:01 by vluo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/includes/libft.h"
# include "../libft/includes/get_next_line_bonus.h"
# include "../minilibx-linux/mlx.h"
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

/* RAY STRUCT

Hold information about 1 ray: 
  - the closest horizontal wall
  - the closest vertival wall
  - the min between them
  - the texture it should have
  - the texture x and y (to scale depending the dist)
  - the height of the line to draw
*/
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

/* MAIN STRUCT*/
typedef struct s_data
{
	void		*mlx;
	void		*win;
	t_img		*img;
	t_player	*p;
	int			**map;
	t_pos		*m_size;
	t_img		*no;
	t_img		*so;
	t_img		*we;
	t_img		*ea;
	t_img		*cur_tex;
	int			floor_col;
	int			ceiling_col;
}	t_data;

/* SRUCT DATA FUNCTIONS */

int			**init_map(void);
t_img		*init_img(t_data *data, void *img_ptr);
t_player	*init_player(t_pos *pos_init, float angle_init);
void		free_data(t_data *data);

/* UTILS */

t_pos		*init_pos(float x, float y);
void		asign_pos(t_pos *pos, float x, float y);
float		dist(t_pos *a, t_pos *b);
float		limit_angle(float nb);
int			trgb(int t, int r, int g, int b);
void		free_tab(char **tab);

/* DRAW */

void		drawmap2d(t_data *data);
void		put_pixel(t_img *img, t_pos *a, int color, int do_free);
void		drawline(t_img *img, t_pos *a, t_pos *b, int color);
void		draw_straight(t_img	*img, t_pos	*a, t_pos *b, int color);

/* RAYS FUNCTIONS */

void		get_hray(float ra, t_pos *hray, t_data *data);
void		get_vray(float ra, t_pos *vray, t_data *data);
void		drawrays(t_data *data);

/* MAIN FUNCTIONS*/

void		display(t_data *data);
int			close_win(t_data *data);
int			handle_key_input(int keysym, t_data *data);

#endif