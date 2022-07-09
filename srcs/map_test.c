/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_function.c                                     :+:      :+:    :+:   */
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

void    exit_with_error(int err_code, char *err_message)
{
    printf("%s\n", err_message);
    exit(err_code);
}

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
        exit_with_error(1, "Error occured while reading map");
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
            exit_with_error(1, "Error occured while reading map");
		map->next->line = cur_line;
		ptrlst->map_y++;
		map = map->next;
	}
}

void	check_map_elements(int idx, int end_idx, int map_counter[], char *line)
{
	char	*valid_elements;

	valid_elements = "01CEP";
	while (*line != '\n' && *line)
	{
		if (!ft_strchr(valid_elements, *line))
			exit_with_error(1, "Wrong element included");
		if (*line == 'C')
			map_counter[C] = 1;
		else if (*line == 'E')
			map_counter[E] = 1;
		else if (*line == 'P')
			map_counter[P] = 1;
        line++;
	}
	if (idx == end_idx)
		if (map_counter[C] == 0 || map_counter[E] == 0 || map_counter[P] == 0)
			exit_with_error(1, "Not enough essesntial element");
}

void	check_map_wall(int line_idx, int end_idx, char *line)
{
	if (line_idx == 1 || line_idx == end_idx)
	{
		while (*line != '\n' && *line)
		{
			if (*line != '1')
				exit_with_error(1, "Map must be surrounded by wall");
			line++;
		}
	}
	else
	{
		if (*line != '1')
			exit_with_error(1, "Map must be surrounded by wall");
		while (*line != '\n' && *line)
			line++;
		if (*(line - 1) != '1')
			exit_with_error(1, "Map must be surrounded by wall");
	}
}

void	check_map_rectangle(t_ptrlst *ptrlst, char *line)
{
    size_t  line_len;

    line_len = ft_strlen(line);
    while (*line != '\n' && *line)
        line++;
    if (*line == '\n')
        line_len--;
	if (ptrlst->map_x == 0)
		ptrlst->map_x = line_len;
	else
	{
		if (ptrlst->map_x != line_len)
			exit_with_error(1, "Map is not rectangle");
	}
}

int	check_map(t_ptrlst *ptrlst)
{
	int		line_idx;
	int		map_counter[3];
	t_map	*map;

    if (ptrlst->map_y < 3)
        exit_with_error(1, "Map is wrong");
	line_idx = 1;
	ft_memset(&map_counter, 0, sizeof(int) * 3);
	map = ptrlst->map_head;
	while (map)
	{
		check_map_elements(line_idx, ptrlst->map_y, map_counter, map->line);
		check_map_wall(line_idx, ptrlst->map_y, map->line);
		check_map_rectangle(ptrlst, map->line);
		map = map->next;
		line_idx++;
	}
}

int	main(int argc, char *argv[])
{
	t_ptrlst	ptrlst;

    if (argc == 2)
    {
        read_map(&ptrlst, argv[1]);
        check_map(&ptrlst);
    }
    printf("Valid Map\n");
    return (0);
}