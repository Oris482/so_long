/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 17:11:27 by jaesjeon          #+#    #+#             */
/*   Updated: 2022/04/06 18:29:20 by jaesjeon         ###   ########.kr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	display_img_data(char *addr, int bpp, int size_len, int endian)
{
	printf("img address = %p\n", addr);
	printf("bpp = %d\n", bpp);
	printf("size_len = %d\n", size_len);
	printf("endian = %d\n", endian);
}

void	get_xpm_img(t_ptrlst *ptrlst, t_imginfo *imginfo, char *filename)
{
	imginfo->img_ptr = mlx_xpm_file_to_image(ptrlst->mlx_ptr, filename, &(imginfo->width), &(imginfo->height));
	printf("%s info : width(%d), height(%d)\n", filename, imginfo->width, imginfo->height);
}

int	display_image(t_ptrlst *ptrlst, t_imginfo *imginfo, int x, int y)
{
	mlx_put_image_to_window(ptrlst->mlx_ptr, ptrlst->win_ptr, imginfo->img_ptr, x, y);
	imginfo->pos_x = x;
	imginfo->pos_y = y;
	return (0);
}

int	move_player(int keycode, t_ptrlst *ptrlst)
{
	int idx_x;
	int	idx_y;

	idx_x = (*ptrlst->imginfo)[PLAYER].pos_x;
	idx_y = (*ptrlst->imginfo)[PLAYER].pos_y;
	mlx_clear_window(ptrlst->mlx_ptr, ptrlst->win_ptr);
	draw_map(ptrlst);
	if (keycode == KEY_W)
		idx_y -= 40;
	else if (keycode == KEY_A)
		idx_x -= 40;
	else if (keycode == KEY_S)
		idx_y += 40;
	else if (keycode == KEY_D)
		idx_x += 40;
	display_image(ptrlst, &(*ptrlst->imginfo)[PLAYER], idx_x, idx_y);
	return (0);
}

int	main(void)
{
	t_ptrlst	ptrlst;
	t_imginfo	imginfo[5];

	ptrlst.mlx_ptr = mlx_init();
	check_map(&ptrlst);
	ptrlst.win_ptr = mlx_new_window(ptrlst.mlx_ptr, ptrlst.map_x, ptrlst.map_y, "SO_LONG_TEST");
	ptrlst.imginfo = &imginfo;
	//mlx_mouse_hook(ptrlst.win_ptr, display_image, &ptrlst);
	//mlx_hook(ptrlst.win_ptr, 2, 0, display_image, &ptrlst);
	get_xpm_img(&ptrlst, &(imginfo[RODE]), "rode.xpm");
	get_xpm_img(&ptrlst, &(imginfo[WALL]), "wall.xpm");
	get_xpm_img(&ptrlst, &(imginfo[ITEM]), "item.xpm");
	get_xpm_img(&ptrlst, &(imginfo[ENDPOINT]), "end.xpm");
	get_xpm_img(&ptrlst, &(imginfo[PLAYER]), "player.xpm");
	draw_map(&ptrlst);
	mlx_hook(ptrlst.win_ptr, 2, 0, move_player, &ptrlst);
	mlx_loop(ptrlst.mlx_ptr);
}
