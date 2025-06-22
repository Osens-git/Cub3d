/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vluo <vluo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 15:20:37 by vluo              #+#    #+#             */
/*   Updated: 2025/06/22 19:37:51 by vluo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

int	close_win(t_data *data)
{
	mlx_mouse_show(data->mlx, data->win);
	free_data(data);
	exit(1);
}

void	init_sprites(t_data *data)
{
	data -> sprites = ft_calloc(2, sizeof(t_sprite *));
	data -> sprites[0] = ft_calloc(1, sizeof(t_sprite));
	data -> sprites[0]-> textures = ft_calloc(6, sizeof(t_img));
	data -> sprites[0]-> textures[0] = init_img(data,
			xpm_img(data, "textures/Hand1.xpm"), 0, 0);
	data -> sprites[0]-> textures[1] = init_img(data,
			xpm_img(data, "textures/Hand2.xpm"), 0, 0);
	data -> sprites[0]-> textures[2] = init_img(data,
			xpm_img(data, "textures/Hand3.xpm"), 0, 0);
	data -> sprites[0]-> textures[3] = init_img(data,
			xpm_img(data, "textures/Hand4.xpm"), 0, 0);
	data -> sprites[0]-> textures[4] = init_img(data,
			xpm_img(data, "textures/Hand5.xpm"), 0, 0);
}

t_data	*init_data(void)
{
	t_data	*data;

	data = ft_calloc(1, sizeof(t_data));
	data -> mlx = mlx_init();
	data -> win = mlx_new_window(data -> mlx, RES_X, RES_Y, "CUB3D");
	data -> img = init_img(data, NULL, RES_X, RES_Y);
	data -> frame = -1;
	init_sprites(data);
	return (data);
}

int	parse_cub(int ac, char **av, t_data *data)
{
	int		start;
	char	**file;

	if (check_arg(ac, av) == 0)
		return (0);
	file = get_file_map(av[1]);
	if (!file)
		return (0);
	start = size_map(data, file);
	if (start == -1)
		return (free_tab(file), 0);
	if (!check_nb_tex_col(file, start) || !parse_elems(data, start, file))
		return (free_tab(file), 0);
	egalize_map(data, start, file);
	if (!check_map(file, start)
		|| !check_surrounded(file, data->m_size->y, start))
		return (free_tab(file), 0);
	data->map = parse_map(data, start, file);
	free_tab(file);
	if (!data -> map)
		return (free_tab(file), 0);
	return (1);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	data = init_data();
	if (!parse_cub(argc, argv, data))
		return (free_data(data), 0);
	data -> minimap = ft_calloc(1, sizeof(t_minimap));
	init_minimap(data);
	display(data);
	mlx_do_key_autorepeatoff(data -> mlx);
	mlx_mouse_hide(data->mlx, data->win);
	mlx_mouse_move(data->mlx, data->win, RES_X / 2, RES_Y / 2);
	mlx_hook(data -> win, 17, 0L, close_win, data);
	mlx_hook(data -> win, 06, 1L << 6, handle_mouse, data);
	mlx_hook(data -> win, 2, 1L << 0, handle_key_input, data);
	mlx_hook(data -> win, 3, 1L << 1, key_up, data);
	mlx_loop_hook(data->mlx, display, data);
	mlx_loop(data -> mlx);
}
