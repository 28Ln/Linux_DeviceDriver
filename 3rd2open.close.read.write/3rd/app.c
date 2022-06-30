#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(void)
{
	char buf[20]="userdata";
	int fd, count;
	fd = open("/dev/test", O_RDWR);
	if(fd < 0)
	{
		perror("open");
		return -1;
	}
	count = write(fd, buf, 20);
	
	printf("<app>buf is [%s]\n", buf);

	count = read(fd, buf, 20);
	

	close(fd);
	return 0;
}
