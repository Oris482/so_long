/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 17:11:27 by jaesjeon          #+#    #+#             */
/*   Updated: 2022/07/16 18:11:08 by jaesjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/so_long.h"

static void	get_xpm_imgs(t_ptrlst *ptrlst, t_imginfo imginfo[])
{
	size_t	idx;

	imginfo[RODE].img_ptr = mlx_xpm_file_to_image(ptrlst->mlx_ptr, \
		"./assets/rode.xpm", &(imginfo[RODE].width), &(imginfo[RODE].height));
	imginfo[WALL].img_ptr = mlx_xpm_file_to_image(ptrlst->mlx_ptr, \
		"./assets/wall.xpm", &(imginfo[WALL].width), &(imginfo[WALL].height));
	imginfo[ITEM].img_ptr = mlx_xpm_file_to_image(ptrlst->mlx_ptr, \
		"./assets/item.xpm", &(imginfo[ITEM].width), &(imginfo[ITEM].height));
	imginfo[END].img_ptr = mlx_xpm_file_to_image(ptrlst->mlx_ptr, \
		"./assets/end.xpm", &(imginfo[END].width), &(imginfo[END].height));
	imginfo[PLAYER].img_ptr = mlx_xpm_file_to_image(ptrlst->mlx_ptr, \
		"./assets/player.xpm", &(imginfo[PLAYER].width), \
		&(imginfo[PLAYER].height));
	idx = 0;
	while (idx <= PLAYER)
	{
		if (imginfo[idx].img_ptr == NULL)
			exit_with_message(1, "Error\nFail to create imgae data");
		idx++;
	}
}

static void	get_next_pos(t_ptrlst *ptrlst, int keycode)
{
	ptrlst->next_pos[X] = ptrlst->cur_pos[X];
	ptrlst->next_pos[Y] = ptrlst->cur_pos[Y];
	if (keycode == KEY_W)
		ptrlst->next_pos[Y] -= 1;
	else if (keycode == KEY_A)
		ptrlst->next_pos[X] -= 1;
	else if (keycode == KEY_S)
		ptrlst->next_pos[Y] += 1;
	else if (keycode == KEY_D)
		ptrlst->next_pos[X] += 1;
}

static int	move_player(int keycode, t_ptrlst *ptrlst)
{
	size_t	*cur_pos;
	size_t	*next_pos;
	int		tmp_prev_tile;

	cur_pos = ptrlst->cur_pos;
	next_pos = ptrlst->next_pos;
	get_next_pos(ptrlst, keycode);
	if (ptrlst->map_arr[next_pos[Y]][next_pos[X]] == WALL)
		return (ERROR);
	tmp_prev_tile = ptrlst->map_arr[next_pos[Y]][next_pos[X]];
	ptrlst->map_arr[next_pos[Y]][next_pos[X]] = PLAYER;
	if (ptrlst->prev_tile == END)
		ptrlst->map_arr[cur_pos[Y]][cur_pos[X]] = END;
	else
		ptrlst->map_arr[cur_pos[Y]][cur_pos[X]] = RODE;
	ptrlst->prev_tile = tmp_prev_tile;
	re_draw_map(ptrlst);
	cur_pos[X] = next_pos[X];
	cur_pos[Y] = next_pos[Y];
	ptrlst->key_counter++;
	printf("counter = %zu\n", ptrlst->key_counter);
	return (PASS);
}

static int	handle_key(int keycode, t_ptrlst *ptrlst)
{
	if (keycode == KEY_ESC)
		destroy_window(ptrlst);
	if (keycode == KEY_W || keycode == KEY_A || \
		keycode == KEY_S || keycode == KEY_D)
	{
		if (move_player(keycode, ptrlst) == ERROR)
			return (PASS);
		if (ptrlst->prev_tile == ITEM)
			ptrlst->elements_counter[C] -= 1;
		else if (ptrlst->prev_tile == END)
		{
			if (ptrlst->elements_counter[C] == 0)
				exit_with_message(0, "Game clear!\n");
			else
				printf("%zu items left to clear game\n", \
				ptrlst->elements_counter[C]);
		}
	}
	return (PASS);
}

int	main(int argc, char *argv[])
{
	t_ptrlst	ptrlst;
	t_imginfo	imginfo[5];

	if (argc == 2)
	{
		ft_memset(&ptrlst, 0, sizeof(ptrlst));
		check_mapfile_extension(argv[1]);
		read_map(&ptrlst, argv[1]);
		check_map(&ptrlst);
		ptrlst.mlx_ptr = mlx_init();
		get_xpm_imgs(&ptrlst, imginfo);
		ptrlst.imginfo = imginfo;
		ptrlst.win_ptr = mlx_new_window(ptrlst.mlx_ptr, \
			ptrlst.map_x * imginfo->width, \
			ptrlst.map_y * imginfo->height, "SO_LONG");
		if (ptrlst.win_ptr == NULL)
			exit_with_message(1, "Error\nWindow create error");
		draw_map(&ptrlst);
		mlx_hook(ptrlst.win_ptr, 17, 1L << 2, destroy_window, &ptrlst);
		mlx_key_hook(ptrlst.win_ptr, handle_key, &ptrlst);
		mlx_loop(ptrlst.mlx_ptr);
	}
	exit_with_message(1, "Error\narguments error");
	return (0);
}
