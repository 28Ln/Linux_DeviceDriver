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
    // 控制命令
    unsigned int cmd = 0x123;

    // 调用打开设备函数。注意O_RDWR是字母O
    fd = open(DEVICE_NAME, O_RDWR);
    // 打开失败
    if (fd == -1)
    {
        printf("[open device %s error]\n", DEVICE_NAME);
        return 0;
    }

    // 调用驱动程序的写操作接口函数
    if (ioctl(fd, cmd) == -1)
    {
        printf("[ioctl device %s error]\n", DEVICE_NAME);
        return 0;
    }

    // 若ret的值为0，表示设备成功关闭
    ret = close(fd);
    printf("[close device %s] ret = %d\n", DEVICE_NAME, ret);

    return 0;
}

