/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jconcent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 21:11:32 by jconcent          #+#    #+#             */
/*   Updated: 2020/11/14 23:08:10 by jconcent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_FDF_H
#define FDF_FDF_H

#include "math.h"
#include "../libft/include/libft.h"
#include "../minilibx/mlx.h"
#include "stdio.h"
#include "fcntl.h"

#define W_W 1000
#define W_H 1000

#define E_MALLOC "Malloc is bad"
#define E_MAP "Map file is invalid"
#define E_MLX "MLX init is bad"
#define E_NULL "Pointer to Null"
#define E_USAGE "Usage: ./fdf <filename>"

# define WHITE			0xFFFFFF
# define RED			0xFF0000
# define ORANGE			0xFF9900
# define DEEP_PINK		0xFF1493
# define YELLOW			0xFFD300
# define AQUAMARINE		0x7FFFD4
# define LIGHT_BLUE		0x00cfe5

# define THISTLE		0xD8BFD8
# define BISQUE			0xFFE4C4
# define BLUE			0xADD8E6
# define LIGHT_PINK		0xFFB6C1
# define LIGHT_SALMON	0xFFA07A
# define PEACH_PUFF		0xFFDAB9
# define LIGHT_GREEN	0x90EE90
# define BLACK			0x000000

typedef struct s_map
{
	int height_max;
	int height_min;
	t_list *heights;
	size_t length;
	size_t width;
}		t_map;

typedef struct s_point
{
	int x;
	int y;
	int z;
}	t_point;

typedef struct s_fdf
{
	int background_color;
	int color;
	int zoom;
	int x_shift;
	int y_shift;
	int proj;
	int bpp;
	int line_size;
	void *mlx;
	void *image;
	void *wnd;
	t_map *map;
	double a;
	double b;
	int e;
	double g;
	float z_alt;
	char *data;
}	t_fdf;

typedef struct s_line
{
	t_point begin;
	t_point end;
}	t_line;

void end_with_error(char *msg, t_fdf **fdf);
void init_graphic(t_fdf **fdf);
void	render(t_fdf *fdf);
int		make_height(int x, int y, t_fdf *fdf);
double percentage(int start, int end, int current);

#endif