/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jconcent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 21:23:08 by jconcent          #+#    #+#             */
/*   Updated: 2020/11/14 23:08:14 by jconcent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		make_height(int x, int y, t_fdf *fdf)
{
	int i;
	int *s;
	t_list *tmp;

	i = 0;
	s = NULL;
	tmp = fdf->map->heights;
	while ((i <= y) && (tmp != NULL))
	{
		if (i == y)
		{
			s = (int *)(tmp->content);
			return (s[x]);
		}
		tmp = tmp->next;
		i++;
	}
	end_with_error("Error", &fdf);
	return (0);
}

double percentage(int start, int end, int current)
{
	double place;
	double dist;

	place = current - start;
	dist = end - start;
	return ((dist == 0) ? 1.0 : (place / dist));
}

void end_with_error(char *msg, t_fdf **fdf)
{
	t_list *tmp;

	if (fdf && (*fdf)->map)
	{
		if ((*fdf)->map->heights)
		{
			while ((*fdf)->map->heights)
			{
				tmp = (*fdf)->map->heights;
				(*fdf)->map->heights = (*fdf)->map->heights->next;
				free(tmp);
			}
		}
		mlx_destroy_image((*fdf)->mlx, (*fdf)->image);
		mlx_destroy_window((*fdf)->mlx, (*fdf)->wnd);
		free((*fdf)->map);
	}
	if (fdf)
		free(*fdf);
	if (msg)
	{
		ft_putendl_fd(msg, 2);
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}