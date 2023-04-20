#include "minirt.h"

int	ray_exit(void)
{
	exit(0);
}

int	key_hook(int keycode, t_minirt *ray)
{
	(void)ray;
	if (keycode == KEY_ESC)
		exit(0);
	return (0);
}

void	add_mlx_hook(t_minirt *ray)
{
	mlx_hook(ray->vars.win, KEYPRESS, 0, key_hook, ray);
	mlx_hook(ray->vars.win, DESTROYNOTIFY, 0, ray_exit, ray);
}
