/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agenisse <agenisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 16:14:46 by agenisse          #+#    #+#             */
/*   Updated: 2024/12/21 17:20:47 by agenisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*ft_get_line(char *save)
{
	int		i;
	char	*str;

	i = 0;
	if (!save[i] || !*save)
		return (NULL);
	while (save[i] && save[i] != '\n')
		i++;
	str = malloc(sizeof(char) * (i + 2));
	if (!str)
		return (NULL);
	i = 0;
	while (save[i] && save[i] != '\n')
	{
		str[i] = save[i];
		i++;
	}
	if (save[i] == '\n')
	{
		str[i] = save[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

static char	*ft_save(char *save)
{
	int		i;
	int		j;
	char	*s;

	i = 0;
	while (save[i] && save[i] != '\n')
		i++;
	if (!save[i])
	{
		free(save);
		return (NULL);
	}
	s = malloc(sizeof(char) * (ft_strlen(save) - i + 1));
	if (!s)
		return (NULL);
	i++;
	j = 0;
	while (save[i])
		s[j++] = save[i++];
	s[j] = '\0';
	free(save);
	return (s);
}

static char	*ft_read_and_save(int fd, char *save)
{
	char	*buff;
	int		read_bytes;

	if (!save)
	{
		save = malloc(sizeof(char));
		if (!save)
			return (NULL);
		save[0] = '\0';
	}
	buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (free(save), NULL);
	read_bytes = 1;
	while (!ft_strchr(save, '\n') && read_bytes != 0)
	{
		read_bytes = read(fd, buff, BUFFER_SIZE);
		if (read_bytes == -1)
			return (free (buff), free(save), NULL);
		buff[read_bytes] = '\0';
		save = ft_strjoin(save, buff);
	}
	free(buff);
	return (save);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*save[4096];

	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		if (save[fd])
			free(save[fd]);
		save[fd] = NULL;
		return (NULL);
	}
	save[fd] = ft_read_and_save(fd, save[fd]);
	if (!save[fd])
		return (NULL);
	line = ft_get_line(save[fd]);
	if (!line)
	{
		free(save[fd]);
		save[fd] = NULL;
		return (NULL);
	}
	save[fd] = ft_save(save[fd]);
	return (line);
}

// // #include <stdio.h>
// // #include <fcntl.h>

// // int main()
// // {
// // 	int fd = open("1char.txt", O_RDONLY);
// // 	char *line;
// // 	while ((line = get_next_line(fd)))
// // 	{
// // 		printf("%s\n", line);
// // 		free(line);
// // 	}
// // 	close(fd);
// // 	return (0);
// }