#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(void)
{
	char buf[20];
	int fd;
	int ret;

	fd = open("/dev/test", O_RDWR);
	if(fd < 0)
	{
		perror("open");
		return -1;
	}

	write(fd, "command-connect", 20);
	
	read(fd, buf, 20);
	printf("<app>buf is [%s]\n", buf);

	close(fd);
	return 0;
}
