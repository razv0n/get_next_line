/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahmi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 11:45:52 by mfahmi            #+#    #+#             */
/*   Updated: 2024/11/22 11:45:54 by mfahmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static int	ft_new_line(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static char	*find_new_line(int fd, char *remainder)
{
	ssize_t	size_of_read;
	char	*buffer;
	char	*ptr;

	buffer = ft_calloc(sizeof(char), (BUFFER_SIZE + 1));
	buffer[0] = '\0';
	while (!ft_new_line(buffer, '\n'))
	{
		size_of_read = read(fd, buffer, BUFFER_SIZE);
		if (size_of_read < 0)
			return (free(remainder), free(buffer), NULL);
		else if (size_of_read == 0)
			break ;
		buffer[size_of_read] = '\0';
		if (!remainder)
			remainder = ft_strdup(buffer);
		else
		{
			ptr = remainder;
			remainder = ft_strjoin(ptr, buffer);
			free(ptr);
		}
	}
	free(buffer);
	return (remainder);
}

static int	line_len(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	return (i);
}

static char	*find_line(char **remainder, int length_line)
{
	char	*line;
	int		i;
	char	*ptr;
	char	*new_reminder;

	ptr = *remainder;
	i = 0;
	line = malloc((length_line + 1) * sizeof(char));
	if (!line)
		return (NULL);
	while (ptr[i] && i < length_line)
	{
		line[i] = ptr[i];
		i++;
	}
	line[i] = '\0';
	free(line);
	new_reminder = ft_substr(ptr, i);
	free(*remainder);
	*remainder = new_reminder;
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*remainder[FD_MAX];
	char		*line;
	int			length_line;

	if (fd < 0 || BUFFER_SIZE <= 0 || FD_MAX <= fd)
		return (NULL);
	remainder[fd] = find_new_line(fd, remainder[fd]);
	if (!remainder[fd])
		return (NULL);
	length_line = line_len(remainder[fd]);
	line = find_line(&remainder[fd], length_line);
	if (!*remainder[fd])
	{
		free(remainder[fd]);
		remainder[fd] = NULL;
	}
	return (line);
}
// int main()
// {
//     int fd1, fd2;
//     char *line1 = NULL;
//     char *line2 = NULL;
//     int i;
//     fd1 = open("roo.txt", O_RDONLY);
//     if (fd1 < 0)
//     {
//         perror("Error opening roo.txt");
//         return (1);
//     }

//     fd2 = open("too.txt", O_RDONLY);
//     if (fd2 < 0)
//     {
//         perror("Error opening too.txt");
//         close(fd1);
//         return (1);
//     }
//     while (1)
//     {
//         i = 0;
//         while (i++ < 4 && (line1 = get_next_line(fd1)))
//              printf("File1: %s", line1);
//         i = 0;
//         while (i++ < 4 && (line2 = get_next_line(fd2)))
//              printf("File2: %s", line2);
//         if (!line1 && !line2)
//             break;
//     }
//     close(fd1);
//     close(fd2);

//     return (0);
// }
