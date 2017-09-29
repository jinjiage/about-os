#include <linux/module.h>
#include <linux/fs.h>

static struct file_system_type yejinlei_fs_type = {
        .owner = THIS_MODULE,
        .name = "yejinlei-fs",
};


static int __init yejinlei_fs_init(void)
{
        register_filesystem(&yejinlei_fs_type);
        return 0;
}

static void __exit yejinlei_fs_exit(void)
{
        unregister_filesystem(&yejinlei_fs_type);
}

module_init(yejinlei_fs_init);
module_exit(yejinlei_fs_exit);
MODULE_LICENSE("GPL");
