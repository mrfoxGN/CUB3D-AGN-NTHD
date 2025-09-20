#include "cube3d.h"
char	*get_next_line(int fd)
{
	static char	*buf[4096];
	char		*line;
	size_t		old_len;

	if (fd < 0 || fd > 4095 || BUFFER_SIZE < 0)
		return (NULL);
	line = NULL;
	if (gnl_strchr_i(buf[fd], '\n') == -1)
	{
		old_len = gnl_strlen(buf[fd]);
		buf[fd] = gnl_expand_buffer(buf[fd], fd);
		if (old_len == gnl_strlen(buf[fd]) && buf[fd])
			line = gnl_substr(buf[fd], 0, gnl_strlen(buf[fd]));
	}
	if (!buf[fd])
		return (NULL);
	if (!line && gnl_strchr_i(buf[fd], '\n') != -1)
		line = gnl_substr(buf[fd], 0, gnl_strchr_i(buf[fd], '\n') + 1);
	if (line)
	{
		buf[fd] = gnl_shrink_buffer(buf[fd], line);
		return (line);
	}
	return (get_next_line(fd));
}
char **read_map(char *file_name,t_game *game)
{
    int fd;
    char *line[2];
    char **map;
}