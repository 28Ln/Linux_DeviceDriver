#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(void)
{
	char buf[20];
	int fd;
	fd = open("/dev/test", O_RDWR);
	if(fd < 0)
	{
		perror("open");
		return -1;
	}

	read(fd, buf, 20);
	printf("<app>read1 buf is [%s]\n", buf);

	write(fd, "command-connect", 20);

	read(fd, buf, 20);
	printf("<app>read2 buf is [%s]\n", buf);

	close(fd);
	return 0;
}
