/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jconcent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 21:21:46 by jconcent          #+#    #+#             */
/*   Updated: 2020/11/14 22:41:48 by jconcent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static t_list *line_work(char *line, const int parts, t_map **map)
{
	int i;
	int heights[parts];
	char *p;

	i = 0;
	p = line;
	while (p && *(p = ft_strrew(p, ft_isspace)))
	{
		heights[i] = ft_atoi(p);
		if ((*map)->height_max < heights[i])
			(*map)->height_max = heights[i];
		if ((*map)->height_min > heights[i])
			(*map)->height_min = heights[i];
		p = ft_strchr(p, ' ');
		i++;
	}
	if (i != parts)
		return (NULL);
	return (ft_lstnew(heights, sizeof(int) * parts));
}

size_t	parts_counter(char const *str, char space)
{
	size_t part;

	part = 0;
	if (!str || *str == '\0')
		return (0);
	while (*str)
	{
		if (*str != space && (*(str + 1) == space || (*(str + 1) == '\0')))
			part++;
		str++;
	}
	return (part);
}

int	reading_map(t_map **map, int fd)
{
	char *line;
	t_list *list;
	size_t parts;
	int reader;

	while ((reader = get_next_line(fd, &line)) > 0)
	{
		parts = parts_counter(line, ' ');
		if ((*map)->length == 0)
			(*map)->length = parts;
		list = line_work(line, parts, map);
		if (!list || (*map)->length != parts)
			end_with_error(E_MAP, NULL);
		ft_lstadd(&((*map)->heights), list);
		(*map)->width++;
		free(line);
	}
	if (reader < 0)
		end_with_error(E_MAP, NULL);
	ft_lstrev(&((*map)->heights));
	return (0);
}

void	init_map(t_map **map)
{
	if (!map)
		end_with_error(E_NULL, NULL);
	*map = ((t_map *)malloc(sizeof(t_map)));
	if (!*map)
		end_with_error(E_MALLOC, NULL);
	ft_bzero(*map, sizeof(t_map));
	(*map)->height_max = INT32_MIN;
	(*map)->height_min = INT32_MAX;
}

int		main(int argc, char **argv)
{
	int fd;
	t_map *map;
	t_fdf *fdf;

	if (argc != 2)
		end_with_error(E_USAGE, NULL);
	if ((fd = open(argv[1], O_RDONLY)) == -1)
		end_with_error(E_MAP, NULL);
	init_map(&map);
	reading_map(&map, fd);
	close(fd);
	init_graphic(&fdf);
	fdf->map = map;
	render(fdf);
	return (0);
}
