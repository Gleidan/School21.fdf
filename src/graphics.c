/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jconcent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 22:32:18 by jconcent          #+#    #+#             */
/*   Updated: 2020/11/14 23:08:42 by jconcent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void init_graphic(t_fdf **fdf)
{
	if (!fdf)
		end_with_error(E_NULL, NULL);
	*fdf = (t_fdf*)malloc(sizeof(t_fdf));
	if (!fdf)
		end_with_error(E_MALLOC, NULL);
	ft_bzero(*fdf, sizeof(t_fdf));
	(*fdf)->proj = 1;
	(*fdf)->zoom = 10;
	(*fdf)->z_alt = 1;
	(*fdf)->x_shift = W_W / 2;
	(*fdf)->y_shift = W_H / 2;
	if (!((*fdf)->mlx = mlx_init()))
		end_with_error(E_MLX, fdf);
	if (!((*fdf)->wnd = mlx_new_window((*fdf)->mlx, W_W, W_H, "Fil De Fer")))
		end_with_error(E_MLX, fdf);
	if (!((*fdf)->image = mlx_new_image((*fdf)->mlx, W_W, W_H)))
		end_with_error(E_MLX, fdf);
	if (!((*fdf)->data = mlx_get_data_addr((*fdf)->image, &((*fdf)->bpp), &((*fdf)->line_size), &((*fdf)->e))))
		end_with_error(E_MLX, fdf);
}

static void make_pixel(t_fdf *fdf, int x, int y)
{
	int i;
	
	if (x >= 0 && x < W_W && y >= 0 && y < W_H)
	{
		i = (x * fdf->bpp / 8) + (y * fdf->line_size);
		fdf->data[i] = (char)fdf->color;
		fdf->data[++i] = (char)(fdf->color >> 8);
		fdf->data[++i] = (char)(fdf->color >> 16);
	}
}

static void	make_background(t_fdf *fdf)
{
	int i;
	int *img;

	i = 0;
	img = (int *)(fdf->data);
	while (i < W_W * W_H)
	{
		img[i] = fdf->background_color;
		i++;
	}
}

static void make_line_render(t_line line, t_fdf *fdf)
{
	t_point s;
	t_point d;
	int err[2];

	color_line(&line, fdf);
	make_projection(&line, &d, fdf);
	s.x = line.begin.x < line.end.x ? 1 : -1;
	s.y = line.begin.y < line.end.y ? 1 : -1;
	err[0] = d.x - d.y;
	while (line.begin.x != line.end.x || line.begin.y != line.end.y)
	{
		make_pixel(fdf, line.begin.x, line.begin.y);
		if ((err[1] = err[0] * 2) > -d.y)
		{
			err[0] -= d.y;
			line.begin.x += s.x;
		}
		if (err[1] < d.x)
		{
			err[0] += d.x;
			line.begin.y += s.y;
		}
	}
}

void	render(t_fdf *fdf)
{
	struct s_line line;

	make_background(fdf);
	line.begin.y = -1;
	while (++line.begin.x < (int)fdf->map->length)
	{
		if (line.begin.x < (int)fdf->map->length - 1)
		{
			line.end.x = line.begin.x + 1;
			line.end.y = line.begin.y;
			make_line_render(line, fdf);
		}
		if (line.begin.y < (int)fdf->map->width - 1)
		{
			line.end.x = line.begin.x;
			line.end.y = line.begin.y + 1;
			make_line_render(line, fdf);
		}
	}
	mlx_put_image_to_window(fdf->mlx, fdf->wnd, fdf->image, 0, 0);
	print_menu(fdf);
}