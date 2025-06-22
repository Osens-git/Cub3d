/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vluo <vluo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 15:20:37 by vluo              #+#    #+#             */
/*   Updated: 2025/06/22 15:41:41 by vluo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	display(t_data *data)
{
	mlx_clear_window(data->mlx, data -> win);
	drawrays(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img->img, 0, 0);
}

t_data	*init_data(void)
{
	t_data	*data;

	data = ft_calloc(1, sizeof(t_data));
	data -> mlx = mlx_init();
	data -> win = mlx_new_window(data -> mlx, RES_X, RES_Y, "CUB3D");
	data -> img = init_img(data, NULL);
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
	if (!data)
		return (exit_mess("Malloc error"), 0);
	if (!parse_cub(argc, argv, data))
		return (free_data(data), 0);
	display(data);
	mlx_do_key_autorepeaton(data -> mlx);
	mlx_hook(data -> win, 17, 0L, close_win, data);
	mlx_hook(data -> win, 2, 1L << 0, handle_key_input, data);
	mlx_loop(data -> mlx);
}
