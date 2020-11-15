/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jconcent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 22:57:03 by jconcent          #+#    #+#             */
/*   Updated: 2020/11/14 23:08:37 by jconcent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int colors(int i, t_fdf *fdf)
{
	double percent = percentage(fdf->map->height_min, fdf->map->height_max, i);

	if (percent == 0.0)
		return (LIGHT_BLUE);
	else if (percent < 0.2)
		return (AQUAMARINE);
	else if (percent < 0.4)
		return (YELLOW);
	else if (percent < 0.6)
		return (DEEP_PINK);
	else if (percent < 0.8)
		return (ORANGE);
	else
		return (RED);
}

void color_line(t_line *line, t_fdf *fdf)
{
	if (make_height((*line).begin.x, (*line).begin.y, fdf) > 0)
		fdf->color = colors(make_height((*line).begin.x, (*line).begin.y, fdf), fdf);
	else if (make_height((*line).end.x, (*line).end.y, fdf) > 0)
		fdf->color = colors(make_height((*line).end.x, (*line).end.y, fdf), fdf);
	else
		fdf->color = WHITE;
}