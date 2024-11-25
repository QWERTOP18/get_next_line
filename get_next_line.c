#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#define __LOG__ printf("%s line %d\n"'__func__.)

#ifdef TEST
int	main(int argc, char **argv)
{
	int	fd;

	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (1);
	close(fd);
	return (0);
}
#endif