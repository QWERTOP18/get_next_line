/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymizukam <ymizukam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 18:47:25 by ymizukam          #+#    #+#             */
/*   Updated: 2024/12/25 18:46:27 by ymizukam         ###   ########.fr       */
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
		str->base[str->size] = '\0';
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
	{
		free(str->base);
		str->base = NULL;
		return (E_ALLOCATE);
	}
	while (index < str->index)
	{
		new_base[index] = str->base[index];
		index++;
	}
	str->size *= 2;
	new_base[str->size] = '\0';
	free(str->base);
	str->base = new_base;
	return (E_NONE);
}

void	release(t_str *str)
{
	free(str->base);
	str->base = NULL;
	str->size = 0;
	str->index = 0;
}

t_err	process_char(t_str *buf, t_str *line, int fd)
{
	char	ch;
	t_err	err;

	err = E_NONE;
	if (buf->index >= buf->size)
		err = allocate(buf, O_READ, fd);
	if (line->index >= line->size)
		err = reallocate(line);
	if (err)
		return (err);
	ch = buf->base[buf->index];
	buf->index++;
	line->base[line->index] = ch;
	line->index++;
	line->base[line->index] = '\0';
	if (ch == '\n')
		return (END_LINE);
	return (E_NONE);
}

char	*get_next_line(int fd)
{
	t_str			line;
	static t_str	buf[MAX_FD];
	t_err			err;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, NULL, 0) == -1)
		return (NULL);
	line.base = NULL;
	err = allocate(&line, O_NONE, fd);
	if (!buf[fd].base)
		err = allocate(&buf[fd], O_READ, fd);
	while (err == E_NONE)
	{
		err = process_char(&buf[fd], &line, fd);
	}
	if (((err == END_LINE || err == END_FILE)) && line.index != 0)
	{
		return (line.base);
	}
	release(&buf[fd]);
	release(&line);
	return (NULL);
}

// #ifdef TEST
// int	main(void)
// {
// 	int		fd;
// 	char	*line;

// 	fd = open("s.txt", O_RDONLY);
// 	while ((line = get_next_line(fd)) != NULL)
// 	{
// 		printf("line=%s\n", line);
// 		free(line);
// 	}
// 	close(fd);
// 	return (0);
// }
// #endif