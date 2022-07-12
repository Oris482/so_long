/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 15:48:11 by jaesjeon          #+#    #+#             */
/*   Updated: 2022/07/12 03:37:40 by jaesjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H
# include "../mlx/mlx.h"
# include "../libft/libft.h"
# include <stdio.h>
# include <sys/signal.h>

# define ERROR -1
# define PASS 1

# define RODE 0
# define WALL 1
# define ITEM 2
# define END 3
# define PLAYER 4

# define C 0
# define E 1
# define P 2

# define KEY_W 13
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_ESC 53

# define X 0
# define Y 1

typedef struct s_map
{
	char			*line;
	size_t			len;
	struct s_map	*next;
}	t_map;

typedef struct s_imginfo
{
	void	*img_ptr;
	int		width;
	int		height;
}	t_imginfo;

typedef struct s_ptrlst
{
	void				*mlx_ptr;
	void				*win_ptr;
	struct s_map		*map_head;
	size_t				map_x;
	size_t				map_y;
	size_t				player_x;
	size_t				player_y;
	int					prev_tile;
	size_t				key_counter;
	size_t				elements_counter[3];
	int					**map_arr;
	struct s_imginfo	*imginfo;
}	t_ptrlst;

void	exit_with_message(int exit_code, char *exit_message);
void	check_mapfile_extension(char *filename);
void	read_map(t_ptrlst *ptrlst, char *map_file);
void	check_map(t_ptrlst *ptrlst);
void	convert_map_to_array(t_ptrlst *ptrlst, t_map *map);
void	free_map_list(t_ptrlst *ptrlst);
void	draw_map(t_ptrlst *ptrlst);
int		destroy_window(t_ptrlst *ptrlst);

#endif
