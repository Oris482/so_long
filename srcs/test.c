#include "../mlx/mlx.h"
#include <stdio.h>
#include "../libft/libft.h"

typedef struct s_vars
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_ptr;
	int		width;
	int		height;
	int		on_off;
} t_vars;

int	display_image(int keycode, t_vars *vars)
{
	printf("keycode = %d\n", keycode);
	mlx_clear_window(vars->mlx_ptr, vars->win_ptr);
	if (vars->on_off == 0)
	{
		vars->img_ptr = mlx_xpm_file_to_image(vars->mlx_ptr, "teapot.xpm", &(vars->width), &(vars->height));
		mlx_put_image_to_window(vars->mlx_ptr, vars->win_ptr, vars->img_ptr, 0, 0);
		vars->on_off = 1;
	}
	else
	{
		vars->img_ptr = mlx_xpm_file_to_image(vars->mlx_ptr, "test.xpm", &(vars->width), &(vars->height));
		mlx_put_image_to_window(vars->mlx_ptr, vars->win_ptr, (vars->img_ptr), 0, 0);
		vars->on_off = 0;
	}
	return (0);
}

int	main(void)
{
	t_vars	vars;

	vars.on_off = 0;
	vars.mlx_ptr = mlx_init();
	vars.win_ptr = mlx_new_window(vars.mlx_ptr, 1300, 1300, "SO_LONG_TEST");
	//mlx_mouse_hook(vars.win_ptr, display_image, &vars);
	mlx_hook(vars.win_ptr, 2, 1L<<0, display_image, &vars);
	mlx_loop(vars.mlx_ptr);
}
