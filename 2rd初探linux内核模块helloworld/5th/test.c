#include <linux/module.h>
#include <linux/init.h>
#include "haha.h"

static int __init test_init(void)
{
    printk("hello world!\n");
	haha();
	return 0;
}

static void __exit test_exit(void)
{
    printk("good bye!\n");
}

module_init(test_init);
module_exit(test_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Leon");
MODULE_VERSION("1.0");
