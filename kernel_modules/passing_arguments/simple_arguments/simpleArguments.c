#include <linux/init.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/kernel.h>

MODULE_LICENSE("Something BSD/GPL");

static short int myshort = 1;   //default values
static int myint = 2020;

module_param(myshort, short, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);
MODULE_PARM_DESC(myshort, "A short integer");

module_param(myint, int, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
MODULE_PARM_DESC(myint, "An integer");

static int __init modpass_init(void)
{
    printk(KERN_INFO "Hello, world with Passing command line arguments\n");
    printk(KERN_INFO "myshort is a short integer: %hd\n", myshort);
    printk(KERN_INFO "myint is an integer: %d\n", myint);
    return 0;
}
static void __exit modpass_exit(void)
{
    printk(KERN_INFO "Goodbye, Hello world passing command line arguments exiting…\n");
}

module_init(modpass_init);
module_exit(modpass_exit);
