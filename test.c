/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprates <lprates@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 14:41:47 by lprates           #+#    #+#             */
/*   Updated: 2021/04/10 19:05:25 by lprates          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <math.h>
#include <stdio.h>
#include "cub3d.h"

int             key_hook(int keycode, t_vars *vars)
{
    printf("Hello, this is key: %i\n", keycode);
}

double	get_angle(int x, int y, int old_x, int old_y)
{
	double dot_res;
	double new_magn;
	double old_magn;

	dot_res = x * old_x + y * old_y;
	new_magn = sqrt(pow(x, 2) + pow(y, 2));
	old_magn = sqrt(pow(old_x, 2) + pow(old_y, 2));
	return (acos(dot_res/(new_magn * old_magn)));
}

int             mouse_hook(int mouse_pos, int x, int y, t_vars *vars)
{
	static int old_x = 10;
	static int old_y = 0;
	double angle;

    printf("Hello, mouse clicked: %i\n", mouse_pos);
	printf("Mouse at: %ix %iy\n", x, y);
	angle = get_angle(x, y, old_x, old_y);
	if (angle)
	{
	printf("Mouse moved: %f radians\n", angle);
	printf("Mouse moved: %f degrees\n", (angle * (180/M_PI)));
	}
	old_x = x;
	old_y = y;
}

int             ft_close(int keycode, t_vars *vars)
{
	if (keycode == 53)
    	mlx_destroy_window(vars->mlx, vars->win);
}

int	ft_resize(int x, int y, t_vars *vars)
{
	printf("window has been resized to %ix %iy\n", x, y);
}

int             main(void)
{
    t_data	img;
	t_vars	vars;
	int i = 0;
	int j = 0;
	int h = 600;
	int v = 800;

    vars.mlx = mlx_init();
    vars.win = mlx_new_window(vars.mlx, h, v, "Hello world!");
    //img.img = mlx_new_image(mlx, 400, 400);
    img.img = mlx_new_image(vars.mlx, h, v);
    img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
                                 &img.endian);
    //img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
      //                           &img.endian);
	
	int color = create_trgb(0, 150, 218, 233);
	int width;
	int height = 0;
	int color_shade = add_shade(0.7, color);
	int color_opos = get_oposite(color);
	i = 0;
	while(i < v)
	{
		j = 0;
		while (j < h)
		{
			if (pow(j-125, 2) + pow(i-150, 2) < pow(100, 2))
				my_mlx_pixel_put(&img, j++, i, 0x00FF0000);
			else if (pow(j-275, 2) + pow(i-150, 2) < pow(100, 2))
				my_mlx_pixel_put(&img, j++, i, 0x00FF0000);
			else
				my_mlx_pixel_put(&img, j++, i, 0x00000000);
		}
		i++;
	}
	mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);
	mlx_key_hook(vars.win, key_hook, &vars);
	mlx_mouse_hook(vars.win, mouse_hook, &vars);
	mlx_hook(vars.win, 2, 1L<<0, ft_close, &vars);
	mlx_hook(vars.win, 25, 1L<<18, ft_resize, &vars);
	mlx_loop(vars.mlx);
}
