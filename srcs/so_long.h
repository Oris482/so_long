/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 15:48:11 by jaesjeon          #+#    #+#             */
/*   Updated: 2022/03/27 22:21:04 by jaesjeon         ###   ########.kr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H
# include "../mlx/mlx.h"
# include "../libft/libft.h"
# include <stdio.h>
#include <sys/signal.h>

# define ERROR -1
# define RODE 0
# define WALL 1
# define ITEM 2
# define ENDPOINT 3
# define PLAYER 4

#define KEY_W 13
#define KEY_A 0
#define KEY_S 1
#define KEY_D 2
#define KEY_ESC 53


typedef struct s_map
{
	char			*line;
	struct s_map	*next;
} t_map;

typedef	struct s_imginfo
{
	void	*img_ptr;
	char	*addr;
	int		pos_x;
	int		pos_y;
	int		width;
	int		height;
	int		bpp;
	int		size_len;
	int		endian;
} t_imginfo;

typedef struct s_ptrlst
{
	void				*mlx_ptr;
	void				*win_ptr;
	struct s_map		*map_head;
	int					map_x;
	int					map_y;
	struct s_imginfo	(*imginfo)[5];
} t_ptrlst;

int	check_map(t_ptrlst *ptrlst);
int	draw_map(t_ptrlst *ptrlst);
int	display_image(t_ptrlst *ptrlst, t_imginfo *imginfo, int x, int y);

#endif
