/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 20:10:31 by jaesjeon          #+#    #+#             */
/*   Updated: 2022/07/12 14:44:02 by jaesjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/so_long.h"

void	check_mapfile_extension(char *filename)
{
	char	*extension;

	extension = ".ber";
	if (ft_strlen(filename) < 5)
		exit_with_message(1, "Error\nfile extension");
	while (*filename)
		filename++;
	filename -= 4;
	while (*filename)
	{
		if (*filename != *extension)
			exit_with_message(1, "Error\nfile extension");
		filename++;
		extension++;
	}
}

static void	check_map_elements(size_t idx, t_ptrlst *ptrlst, char *line)
{
	char	*valid_elements;

	valid_elements = "01CEP";
	while (*line != '\n' && *line)
	{
		if (!ft_strchr(valid_elements, *line))
			exit_with_message(1, "Error\nWrong element included");
		if (*line == 'C')
			ptrlst->elements_counter[C] += 1;
		else if (*line == 'E')
			ptrlst->elements_counter[E] += 1;
		else if (*line == 'P')
		{
			if (ptrlst->elements_counter[P] == 1)
				*line = '0';
			else
				ptrlst->elements_counter[P] = 1;
		}
		line++;
	}
	if (idx == ptrlst->map_y)
		if (ptrlst->elements_counter[C] == 0 \
		|| ptrlst->elements_counter[E] == 0 || ptrlst->elements_counter[P] == 0)
			exit_with_message(1, "Error\nNot enough essesntial element");
}

static void	check_map_wall(size_t line_idx, size_t end_idx, char *line)
{
	if (line_idx == 1 || line_idx == end_idx)
	{
		while (*line != '\n' && *line)
		{
			if (*line != '1')
				exit_with_message(1, "Error\nMap must be surrounded by wall");
			line++;
		}
	}
	else
	{
		if (*line != '1')
			exit_with_message(1, "Error\nMap must be surrounded by wall");
		while (*line != '\n' && *line)
			line++;
		if (*(line - 1) != '1')
			exit_with_message(1, "Error\nMap must be surrounded by wall");
	}
}

static void	check_map_rectangle(t_ptrlst *ptrlst, char *line)
{
	size_t	line_len;

	line_len = ft_strlen(line);
	if (line_len < 3)
		exit_with_message(1, "Error\nInvalid Map");
	while (*line != '\n' && *line)
		line++;
	if (*line == '\n')
		line_len--;
	if (ptrlst->map_x == 0)
		ptrlst->map_x = line_len;
	else
	{
		if (ptrlst->map_x != line_len)
			exit_with_message(1, "Error\nMap is not rectangle");
	}
}

void	check_map(t_ptrlst *ptrlst)
{
	size_t	line_idx;
	t_map	*map;

	if (ptrlst->map_y < 3)
		exit_with_message(1, "Error\nInvalid Map");
	line_idx = 1;
	map = ptrlst->map_head;
	while (map)
	{
		check_map_elements(line_idx, ptrlst, map->line);
		check_map_wall(line_idx, ptrlst->map_y, map->line);
		check_map_rectangle(ptrlst, map->line);
		map = map->next;
		line_idx++;
	}
	convert_map_to_array(ptrlst, ptrlst->map_head);
	free_map_list(ptrlst);
}
