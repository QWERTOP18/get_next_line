/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymizukam <ymizukam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 09:50:16 by ymizukam          #+#    #+#             */
/*   Updated: 2024/12/02 11:30:35 by ymizukam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "get_next_line_bonus.h"

// char	*get_next_line(int fd)
// {
// 	static t_remain	remain_head;

// 	if (remain_head == NULL)
// }

// #ifdef TEST
// # include <string.h>
// int	main(int argc, char **argv)
// {
// 	int		fd;
// 	int		c;
// 	char	*line;

// 	fd = 0;
// 	if (argc > 1)
// 		fd = open(argv[1], O_RDONLY);
// 	if (fd < 0)
// 		return (1);
// 	while (1)
// 	{
// 		line = get_next_line(fd);
// 		printf("%s\n", line);
// 		if (!line)
// 		{
// 			free(line);
// 			break ;
// 		}
// 		free(line);
// 	}
// 	close(fd);
// 	return (0);
// }
// #endif