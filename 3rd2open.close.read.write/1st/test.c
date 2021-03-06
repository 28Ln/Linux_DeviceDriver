#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/cdev.h>

#define DEBUG_SWITCH    1
#if DEBUG_SWITCH
	#define P_DEBUG(fmt, args...)   printk("<1>" "<kernel>[%s]"fmt, __FUNCTION__, ##args)
#else
	#define P_DEBUG(fmt, args...)   printk("<7>" "<kernel>[%s]"fmt, __FUNCTION__, ##args)
#endif

unsigned int major = 150;
unsigned int minor = 0;
dev_t devno;
struct cdev test_cdev;

int test_open(struct inode *node, struct file *filp)
{
	P_DEBUG("open device\n");
	return 0;
}

int test_close(struct inode *node, struct file *filp)
{
	P_DEBUG("close device\n");
	return 0;
}

struct file_operations test_fops = {
	.open = test_open,
	.release = test_close,
};

static int __init test_init(void)	//模块初始化函数
{
	int result = 0;

	/*1.申请设备号*/
	if(major){						
		devno = MKDEV(major, minor);
		result = register_chrdev_region(devno, 1, "test new driver");
	}else{
		result = alloc_chrdev_region(&devno, minor, 1, "test alloc diver");
		major = MAJOR(devno);
		minor = MINOR(devno);
	}

	if(result < 0){
		P_DEBUG("register devno errno!\n");
		goto err0;
	}

	printk("major[%d] minor[%d]\n", major, minor);

	/*2.注册设备*/
	cdev_init(&test_cdev, &test_fops);
	test_cdev.owner = THIS_MODULE;
	result = cdev_add(&test_cdev, devno, 1);
	if(result < 0){
		P_DEBUG("cdev_add errno!\n");
		goto err1;
	}

	printk("hello kernel\n");
	return 0;

err1:
	unregister_chrdev_region(devno, 1);
err0:
	return result;
}

static void __exit test_exit(void)		//模块卸载函数
{
	/*1.从内核中删除cdev*/
	cdev_del(&test_cdev);
	/*2.注销设备号*/
	unregister_chrdev_region(devno, 1);

	printk("good bye kernel\n");
}

module_init(test_init);
module_exit(test_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Leon");
MODULE_VERSION("v0.1");
