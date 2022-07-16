/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 20:00:24 by jaesjeon          #+#    #+#             */
/*   Updated: 2022/07/16 18:11:31 by jaesjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/so_long.h"

void	exit_with_message(int exit_code, char *exit_message)
{
	printf("%s\n", exit_message);
	exit(exit_code);
}

int	destroy_window(t_ptrlst *ptrlst)
{
	mlx_destroy_window(ptrlst->mlx_ptr, ptrlst->win_ptr);
	exit_with_message(0, "Exit\n");
	return (0);
}

void	free_map_list(t_ptrlst *ptrlst)
{
	t_map	*cur_node;
	t_map	*tmp_node;

	cur_node = ptrlst->map_head;
	while (cur_node)
	{
		tmp_node = cur_node;
		free(cur_node->line);
		cur_node = cur_node->next;
		free(tmp_node);
	}
}

int	convert_alpha(char c)
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

void	init_player_position(t_ptrlst *ptrlst, size_t pos_x, size_t pos_y)
{
	ptrlst->cur_pos[X] = pos_x;
	ptrlst->cur_pos[Y] = pos_y;
}
