/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_function.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 17:11:46 by jaesjeon          #+#    #+#             */
/*   Updated: 2022/07/16 18:11:35 by jaesjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/so_long.h"
#include <fcntl.h>
#include <sys/fcntl.h>
#include "get_next_line.h"

void	read_map(t_ptrlst *ptrlst, char *map_file)
{
	int		fd;
	char	*cur_line;
	t_map	*map;

	map = (t_map *)ft_calloc(1, sizeof(t_map));
	ptrlst->map_head = map;
	fd = open(map_file, O_RDONLY);
	cur_line = get_next_line(fd);
	if (map == NULL || fd < 0 || cur_line == NULL)
		exit_with_message(1, "Error\nError occured while reading map");
	map->line = cur_line;
	ptrlst->map_x = 0;
	ptrlst->map_y = 1;
	while (1)
	{
		cur_line = get_next_line(fd);
		if (cur_line == NULL)
			break ;
		map->next = (t_map *)ft_calloc(1, sizeof(t_map));
		if (map->next == NULL)
			exit_with_message(1, "Error\nError occured while reading map");
		map->next->line = cur_line;
		ptrlst->map_y++;
		map = map->next;
	}
}

void	convert_map_to_array(t_ptrlst *ptrlst, t_map *map)
{
	size_t	idx[2];
	char	*line;

	ptrlst->map_arr = (int **)malloc(ptrlst->map_y * sizeof(int *));
	if (ptrlst->map_arr == NULL)
		exit_with_message(1, "Error\nMalloc failed");
	idx[Y] = 0;
	while (map)
	{
		idx[X] = 0;
		(ptrlst->map_arr)[idx[Y]] = (int *)malloc(ptrlst->map_x * sizeof(int));
		if ((ptrlst->map_arr)[idx[Y]] == NULL)
			exit_with_message(1, "Error\nMalloc failed");
		line = map->line;
		while (*line != '\n' && *line)
		{
			(ptrlst->map_arr)[idx[Y]][idx[X]] = convert_alpha(*line);
			if (*line == 'P' && ptrlst->cur_pos[X] == 0)
				init_player_position(ptrlst, idx[X], idx[Y]);
			idx[X]++;
			line++;
		}
		idx[Y]++;
		map = map->next;
	}
}

void	draw_map(t_ptrlst *ptrlst)
{
	size_t	x_idx;
	size_t	y_idx;
	size_t	element;

	y_idx = 0;
	while (y_idx < ptrlst->map_y)
	{
		x_idx = 0;
		while (x_idx < ptrlst->map_x)
		{
			element = ptrlst->map_arr[y_idx][x_idx];
			mlx_put_image_to_window(ptrlst->mlx_ptr, ptrlst->win_ptr, \
				ptrlst->imginfo[element].img_ptr, \
				x_idx * ptrlst->imginfo[element].width, \
				y_idx * ptrlst->imginfo[element].height);
			x_idx++;
		}
		y_idx++;
	}
}

void	re_draw_map(t_ptrlst *ptrlst)
{
	size_t	prev_pos[2];
	size_t	prev_element;
	size_t	cur_pos[2];
	size_t	cur_element;

	prev_pos[X] = ptrlst->cur_pos[X];
	prev_pos[Y] = ptrlst->cur_pos[Y];
	prev_element = ptrlst->map_arr[prev_pos[Y]][prev_pos[X]];
	cur_pos[X] = ptrlst->next_pos[X];
	cur_pos[Y] = ptrlst->next_pos[Y];
	cur_element = ptrlst->map_arr[cur_pos[Y]][cur_pos[X]];
	mlx_put_image_to_window(ptrlst->mlx_ptr, ptrlst->win_ptr, \
		ptrlst->imginfo[prev_element].img_ptr, \
		prev_pos[X] * ptrlst->imginfo[prev_element].width, \
		prev_pos[Y] * ptrlst->imginfo[prev_element].height);
	mlx_put_image_to_window(ptrlst->mlx_ptr, ptrlst->win_ptr, \
		ptrlst->imginfo[cur_element].img_ptr, \
		cur_pos[X] * ptrlst->imginfo[cur_element].width, \
		cur_pos[Y] * ptrlst->imginfo[cur_element].height);
}
