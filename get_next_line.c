/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agenisse <agenisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 11:25:32 by agenisse          #+#    #+#             */
/*   Updated: 2024/12/10 18:00:49 by agenisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_read(int fd, char *buff)
{
	char	*temp_buff;
	int		bytes_read;

	temp_buff = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!temp_buff)
		return (NULL);
	bytes_read = read(fd, temp_buff, BUFFER_SIZE);
	if (bytes_read <= 0)
	{
		free(temp_buff);
		return (NULL);
	}										// LA CA SEGFAULT, TA FONCTION C NUL, ELLE DEPEND DE LA TAILLE DU BUFF ET LIT PAS PLUS
	buff = ft_strjoin(buff, temp_buff);
	free(temp_buff);
	return (buff);
}

char	*get_line(char *line, char *stock)
{
	int	i;

	i = 0;
	while (stock[i] != '\n')
	{
		line[i] = stock[i];
		i++;
	}
	line[i] = '\n';
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*stock;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!line)
		return (NULL);
	if (!stock)
		stock = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!stock)
		return (NULL);
	stock = ft_read(fd, stock); // PROBLEME ICI 
	stock = ft_read(fd, stock);
	
	if (!stock)
		return (NULL);
	line = get_line(line, stock);
	return (line);
}

int	main(void)
{
	int		fd;
	char	*line;

	fd = open("test.txt", O_RDONLY);
	line = get_next_line(fd);
	printf("%s", line);    // LA FAUT APPELER PLLUSIEURS FOIS TOCARD 
	line = get_next_line(fd);
	printf("%s", line);
	free(line);
	return (0);
}
