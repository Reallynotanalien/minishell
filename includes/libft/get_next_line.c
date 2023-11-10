/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kafortin <kafortin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 10:22:48 by kafortin          #+#    #+#             */
/*   Updated: 2023/11/06 16:35:06 by kafortin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*join_free(char *text, const char *buffer)
{
	char			*temp;
	unsigned int	len1;
	unsigned int	len2;

	len1 = find_len_until(text, '\0');
	len2 = find_len_until(buffer, '\0');
	if (!null_calloc(&temp, sizeof (char), (len1 + len2 + 1)))
	{
		free_if_not_empty(&text);
		return (NULL);
	}
	copy_from_src(temp, text, len1);
	copy_from_src(temp + len1, buffer, len2);
	free_if_not_empty(&text);
	return (temp);
}

char	*read_text(int fd, char **text)
{
	char	*buffer;
	int		bytes;

	bytes = 2;
	if (!null_calloc(&buffer, sizeof (char), 2 + 1))
	{
		free_if_not_empty(&*text);
		return (NULL);
	}
	while (bytes == 2)
	{
		bytes = read(fd, buffer, 2);
		if ((bytes == 0 && find_len_until(*text, '\0') == 0) || bytes == -1)
		{
			free_if_not_empty(&buffer);
			free_if_not_empty(&*text);
			return (NULL);
		}
		buffer[bytes] = '\0';
		*text = join_free(*text, buffer);
		if (scan_for_nl(buffer) == 1)
			break ;
	}
	free_if_not_empty(&buffer);
	return (*text);
}

char	*erase_returned_line(char *text, unsigned int llen)
{
	unsigned int	tlen;
	unsigned int	count;
	char			*temp;

	count = 0;
	tlen = find_len_until(text, '\0');
	if (!null_calloc(&temp, sizeof (char), ((tlen - llen) + 2)))
		temp = NULL;
	while (temp && text[llen - 1] != '\0')
		temp[count++] = text[llen++];
	free_if_not_empty(&text);
	return (temp);
}

int	get_next_line(int fd, char **line)
{
	static char		*text;
	unsigned int	llen;

	if (fd < 0)
		return (0);
	if (!text)
		if (!null_calloc(&text, sizeof (char), 1))
			return (0);
	if (scan_for_nl(text) == 0)
		text = read_text(fd, &text);
	if (!text)
		return (0);
	llen = find_len_until(text, '\n');
	if (!null_calloc(line, sizeof (char), (llen + 1)))
	{
		free_if_not_empty(&text);
		return (0);
	}
	*line = copy_from_src(*line, text, (llen - 1));
	text = erase_returned_line(text, llen);
	return (1);
}
