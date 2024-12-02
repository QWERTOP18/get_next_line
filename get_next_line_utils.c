/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymizukam <ymizukam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 13:29:32 by ymizukam          #+#    #+#             */
/*   Updated: 2024/12/02 12:34:38 by ymizukam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_realloc(char *buf, ssize_t len)
{
	char	*new;
	int		i;

	new = malloc(len + BUFFER_SIZE + 1);
	if (!new)
		return (NULL);
	i = 0;
	while (buf[i])
	{
		new[i] = buf[i];
		i++;
	}
	new[i] = '\0';
	free(buf);
	return (new);
}
