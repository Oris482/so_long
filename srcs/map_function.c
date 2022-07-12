/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_function.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 17:11:46 by jaesjeon          #+#    #+#             */
/*   Updated: 2022/07/12 03:37:14 by jaesjeon         ###   ########.fr       */
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

static int	convert_alpha(char c)
{
	if (c == '0')
		return (RODE);
	else if (c == '1')
		return (WALL);
	else if (c == 'C')
		return (ITEM);
	else if (c == 'E')
		return (END);
	else if (c == 'P')
		return (PLAYER);
	else
		return (ERROR);
}

static void	init_player_position(t_ptrlst *ptrlst, size_t pos_x, size_t pos_y)
{
	ptrlst->player_x = pos_x;
	ptrlst->player_y = pos_y;
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
			if (*line == 'P' && ptrlst->player_x == 0)
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
	size_t	target;

	y_idx = 0;
	while (y_idx < ptrlst->map_y)
	{
		x_idx = 0;
		while (x_idx < ptrlst->map_x)
		{
			target = ptrlst->map_arr[y_idx][x_idx];
			mlx_put_image_to_window(ptrlst->mlx_ptr, ptrlst->win_ptr, \
				ptrlst->imginfo[target].img_ptr, \
				x_idx * ptrlst->imginfo[target].width, \
				y_idx * ptrlst->imginfo[target].height);
			x_idx++;
		}
		y_idx++;
	}
}
