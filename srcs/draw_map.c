/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 17:11:46 by jaesjeon          #+#    #+#             */
/*   Updated: 2022/04/06 19:57:00 by jaesjeon         ###   ########.kr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <fcntl.h>
#include <sys/fcntl.h>
#include "get_next_line.h"

int	read_map(t_ptrlst *ptrlst)
{
	int	fd;
	t_map	*map;

	map = (t_map *)ft_calloc(1, sizeof(t_map));
	ptrlst->map_head = map;
	fd = open("./map.ber", O_RDONLY);
	if (map == NULL || fd < 0)
		return (ERROR);
	map->line = get_next_line(fd);
	map->len = ft_strlen(map->line);
	ptrlst->map_y = 0;
	while (map->line)
	{
		map->next = (t_map *)ft_calloc(1, sizeof(t_map));
		if (map->next == NULL)
			return (ERROR);
		map = map->next;
		map->line = get_next_line(fd);
		map->len = ft_strlen(map->line);
		ptrlst->map_y++;
	}
	return (1);
}

int	check_map(t_ptrlst *ptrlst)
{
	ptrlst->map_arr = (char **)ft_calloc(1, ptrlst->map_y);
	if (ptrlst->map_arr == NULL)
		return (NULL);
}

int	draw_map(t_ptrlst *ptrlst)
{
	char	*line;
	int		idx_x;
	int		idx_y;

	if (!read_map(ptrlst))
		return (ERROR);
	line = ptrlst->map_head->line;
	idx_y = 0;
	while (line)
	{
		idx_x = 0;
		while (*line)
		{
			if (*line == '0')
				;
			else if (*line == '1')
				display_image(ptrlst, &(*ptrlst->imginfo)[WALL], idx_x * 40, idx_y * 40);
			else if (*line == 'C')
				display_image(ptrlst, &(*ptrlst->imginfo)[ITEM], idx_x * 40, idx_y * 40);
			else if (*line == 'E')
				display_image(ptrlst, &(*ptrlst->imginfo)[ENDPOINT], idx_x * 40, idx_y * 40);
			else if (*line == 'P')
				display_image(ptrlst, &(*ptrlst->imginfo)[RODE], idx_x * 40, idx_y * 40);
			else if (*line == '\n') 
				;
			else
				return (0);
			idx_x++;
			line++;
		}
		ptrlst->imginfo[PLAYER]->pos_x = 40;
		ptrlst->imginfo[PLAYER]->pos_y = 40;
		idx_y++;
		ptrlst->map_head = ptrlst->map_head->next;
		line = ptrlst->map_head->line;
	}
	return (0);
}
