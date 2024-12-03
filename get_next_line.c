/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymizukam <ymizukam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 12:19:30 by ymizukam          #+#    #+#             */
/*   Updated: 2024/12/03 17:23:57 by ymizukam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_err	allocate(t_str *str, t_opt opt, int fd)
{
	if (!str->base)
		str->base = malloc(BUFFER_SIZE + 1);
	if (!str->base)
		return (E_ALLOCATE);
	str->size = BUFFER_SIZE;
	str->index = 0;
	if (opt == O_READ)
	{
		str->size = read(fd, str->base, BUFFER_SIZE);
		if (str->size < 0)
			return (E_READ);
		if (str->size == 0)
			return (END_FILE);
	}
	str->base[str->size] = '\0';
	return (E_NONE);
}

t_err	reallocate(t_str *str)
{
	char	*new_base;
	ssize_t	index;

	index = 0;
	new_base = malloc(str->size * 2 + 1);
	if (!new_base)
		return (free(str->base), E_ALLOCATE);
	while (index < str->index)
	{
		new_base[index] = str->base[index];
		index++;
	}
	str->base = new_base;
	str->size *= 2;
	new_base[str->size] = '\0';
	free(str->base);
	return (E_NONE);
}

t_err	process_char(t_str *buf, t_str *line, int fd)
{
	char	ch;
	t_err	err;

	if (buf->index >= buf->size)
		err = allocate(buf, O_READ, fd);
	if (line->index >= buf->size)
		err = reallocate(line);
	if (err)
		return (err);
	ch = buf->base[buf->index];
}

char	*get_next_line(int fd)
{
	t_str			line;
	static t_str	buf;
	t_err			err;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, NULL, 0) == -1)
		return (NULL);
	line.base = NULL;
	err = allocate(&line, O_NONE, fd);
	err = allocate(&buf, O_READ, fd);
	while (err == E_NONE)
	{
		err = process_char(&buf, &line, fd);
	}
	if (err == END_LINE || err == END_FILE) //) && line.index != 0)
	{
		return (line.base);
	}
	buf.size = 0;
	buf.index = 0; // strfree
	return (free(line.base), free(buf.base), NULL);
}

// #ifdef TEST
// # include <string.h>
// int	main(int argc, char **argv)
// {
// 	int		fd;
// 	char	*line;

// 	fd = 0;
// 	if (argc > 1)
// 		fd = open(argv[1], O_RDONLY);
// 	if (fd < 0)
// 		return (1);
// 	while (1)
// 	{
// 		line = get_next_line(fd);
// 		if (!line)
// 		{
// 			free(line);
// 			break ;
// 		}
// 		printf("%s", line);
// 		free(line);
// 	}
// 	close(fd);
// 	return (0);
// }
// #endif