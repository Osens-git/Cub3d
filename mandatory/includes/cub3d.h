/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vluo <vluo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 13:23:04 by vluo              #+#    #+#             */
/*   Updated: 2025/06/22 19:31:35 by vluo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../../libft/includes/libft.h"
# include "../../libft/includes/get_next_line_bonus.h"
# include "../../minilibx-linux/mlx.h"
# include <unistd.h>
# include <stdlib.h>
# include <X11/keysym.h>
# include <stdio.h>
# include <math.h>
# include <fcntl.h>

# define CYAN		"\033[1;96m"
# define RESET		"\033[0m"
# define RED		"\033[1;31m"
# define GREY 		"\033[0;90m"

# define EXIT_COLOR "colors are not numbers\nor must be in a range of 0-255"
# define EXIT_NB_RGB "There must be 3 color, no more, no less"
# define EXIT_NB_COL "There must be 2 colors in Map"
# define EXIT_NB_TEX "There must be 4 textures in Map\nNO, SO, EA, WE"
# define EXIT_MAP "Map must be surrounded by walls or spaces"

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

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}	t_color;

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

/* PARSING */

char		**get_file_map(char *file);

// CHECKS
int			check_arg(int ac, char **av);
int			check_nb_tex_col(char **file, int start);
int			check_surrounded(char **map, int y, int st);
int			check_map(char **file, int start);

// PARSING

int			size_map(t_data *data, char **f);
void		egalize_map(t_data *data, int start, char **file);
int			parse_elems(t_data *data, int start, char **file);
int			**parse_map(t_data *data, int start, char **file);

/* SRUCT DATA FUNCTIONS */

t_img		*init_img(t_data *data, void *img_ptr);
t_player	*init_player(t_data *data, t_pos *pos_init, char dir);
void		free_data(t_data *data);

/* UTILS */

t_pos		*init_pos(float x, float y);
void		asign_pos(t_pos *pos, float x, float y);
float		dist(t_pos *a, t_pos *b);
float		limit_angle(float nb);
int			trgb(int t, int r, int g, int b);
char		*ft_strcpy(char *dest, char *src);
int			check_limits(t_color *color);
void		free_tab(char **tab);
void		free_tab_int(int **t);
void		free_img(t_data *data, t_img *img);
int			exit_mess(char *message);

/* DRAW */

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