// 模块
#include <linux/module.h>
// 内核
#include <linux/kernel.h>
// struct file_operations
#include <linux/fs.h>
// copy_to_user() & copy_from_user
#include <linux/uaccess.h>

// rwbuf.c,  driver for virtual char-device
#define RW_CLEAR 0x123
// 设备名
#define DEVICE_NAME "rwbuf"

// buffer数组的最大长度
#define RWBUF_MAX_SIZE 200
// buffer数组的实际长度
static int rwlen = 0;
// 设备中存储字符串的相关数组
static char rwbuf[RWBUF_MAX_SIZE];

// 同一时间只允许一个打开的锁机制：0表示未被使用，1表示已被使用
static int inuse = 0;

// 设备的打开：返回-1表示错误；返回0表示成功
int rwbuf_open(struct inode *inode, struct file *file)
{
    // 如果已被使用，报错
    if (inuse == 1)
    {
        return -1;
    }
    // 未被使用
    else
    {
        // 上锁，标志为已被使用
        inuse = 1;
        // increase the use count in struct module
        try_module_get(THIS_MODULE);
        return 0;
    }
}

// 设备的关闭：只返回0表示成功无法表示报错
int rwbuf_release(struct inode *inode, struct file *file)
{
    // 去锁，标志为未被使用
    inuse = 0;
    // decrease the use count in struct module
    module_put(THIS_MODULE);
    return 0;
}

// 设备的读操作：返回-1表示错误；返回(0, RWBUF_MAX_SIZE]表示成功
ssize_t rwbuf_read(struct file *file, char *buf, size_t count, loff_t *f_pos)
{
    // 判断读取的长度是否有效
    if (rwlen > 0 && rwlen <= RWBUF_MAX_SIZE)
    {
        // 从内核空间rwbuf复制到用户空间buf
        copy_to_user(buf, rwbuf, count);
        printk("[rwbuf_read-success]the size of rwlen after read = %s len=%d \n", rwbuf ,rwlen);
        return count;
    }
    else
    {
        printk("[rwbuf_read-error] rwlen = %d\n", rwlen);
        return -1;
    }
}

// 设备的写操作接：返回-1表示错误；返回(0, RWBUF_MAX_SIZE]表示成功
ssize_t rwbuf_write(struct file *file, const char *buf, size_t count, loff_t *f_pos)
{
    // 判断写入的长度是否有效
    if (count > 0 && count <= RWBUF_MAX_SIZE)
    {
        // 从用户空间buf复制到内核空间rwbuf
        copy_from_user(rwbuf, buf, count);
        // rwlen字符串的长度为buf的长度
        rwlen = count;
        printk("[rwbuf_write-success] the size of rwlen after write = %s len=%d \n", rwbuf ,rwlen);
        return count;
    }
    else
    {
        printk("[rwbuf_write-error] length of string = %d\n", count);
        return -1;
    }
}

// 设备的ioctl：返回-1表示错误；返回0表示成功
long rwbuf_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
    printk("[RW_CLEAR:%x],[cmd:%x]\n", RW_CLEAR, cmd);
    // 命令
    if (cmd == RW_CLEAR)
    {
        // 字符串的长度设置为0，表示清零
        rwlen = 0;
        printk("[rwbuf_ioctl-success] the size of rwlen after ioctl = %d\n", rwlen);
        return 0;
    }
    // 无此命令时
    else
    {
        printk("[rwbuf_ioctl-error] the size of rwlen after ioctl = %d\n", rwlen);
        return -1;
    }
}

// rwbuf_fops要在rwf_buf_init()前面声明，因为register_chrdev()函数要使用到
static struct file_operations rwbuf_fops =
    {
        open : rwbuf_open,
        release : rwbuf_release,
        read : rwbuf_read,
        write : rwbuf_write,
        unlocked_ioctl : rwbuf_ioctl
    };

// module_init()内的初始化函数：返回-1表示错误；返回0表示成功
static int __init rwbuf_init(void)
{
    printk("Hello world\n");

    // 表示注册成功与否：-1表示失败，0表示成功（同register_chrdev返回值）。初始化为-1
    int ret = -1;
    /*
	参数1：设备的种类，即主设备号
	参数2：设备的名称
	参数3：和VFS对接的接口，即上面的结构体变量
	*/
    ret = register_chrdev(60, DEVICE_NAME, &rwbuf_fops);
    // 注册失败
    if (ret == -1)
    {
        printk("[rwbuf_init-register-failed]\n");
    }
    // 注册成功
    else
    {
        printk("[rwbuf_init-register-success]\n");
    }
    // 返回ret（同register_chrdev返回值）
    return ret;
}

// module_exit()内的退出函数。
static void __exit rwbuf_exit(void)
{
    unregister_chrdev(60, DEVICE_NAME);
    printk("[rwbuf_exit-unregister-success]\n");
}

// 内核模块入口,相当于main()函数,完成模块初始化
module_init(rwbuf_init);
// 卸载时调用的函数入口,完成模块卸载
module_exit(rwbuf_exit);
// GPL协议证书
MODULE_LICENSE("GPL");

