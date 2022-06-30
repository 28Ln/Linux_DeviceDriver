#include <stdio.h>
// 为了open()中的O_RDWR
#include <fcntl.h>
// #include <unistd.h>
// #include <sys/types.h>
// #include <sys/stat.h>

// 定义设备进入点（设备名）
#define DEVICE_NAME "/dev/rwbuf"

int main()
{
    // 声明文件描述符
    int fd;
    // 记录关闭设备的返回值
    int ret;
    // 读取到设备的结果
    char buff[100];

    // 调用打开设备函数。注意O_RDWR是字母O
    fd = open(DEVICE_NAME, O_RDWR);
    // 打开失败
    if (fd == -1)
    {
        printf("[open device %s error]\n", DEVICE_NAME);
        return 0;
    }

    // 调用驱动程序的写操作接口函数
    if (write(fd, "mytest", 5) == -1)
    {
        printf("[write device %s error]\n", DEVICE_NAME);
        return 0;
    }

    // 调用驱动程序的读操作接口函数
    if (read(fd, buff, 5) == -1)
    {
        printf("[read device %s error]\n", DEVICE_NAME);
        return 0;
    }
    // 读取成功
    else
    {
        buff[5] = '\0';
        printf("[buff] %s\n", buff);
    }

    // 若ret的值为0，表示设备成功关闭
    ret = close(fd);
    printf("[close device %s] ret = %d\n", DEVICE_NAME, ret);

    return 0;
}

