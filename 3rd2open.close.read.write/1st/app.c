#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(void)
{
	int fd;
	fd = open("/dev/test5", O_RDWR);
	if(fd < 0)
	{
		perror("open");
		return -1;
	}
	printf("open /dev/test5 success \n");
	close(fd);
	return 0;
}
