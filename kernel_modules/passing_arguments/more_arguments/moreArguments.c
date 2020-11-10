#include <linux/init.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/kernel.h>

MODULE_LICENSE("Something");

static char *mystring = "hello";
module_param(mystring, charp, 0);

static int array1[2] = {1, 2};
module_param_array(array1, int, NULL, 0); //not interested in count (NULL is passed)
int count;
static int array2[3] = {3, 4, 5};
module_param_array(array2, int, &count, 0); //put count into "count" variable

static int __init modpass_init(void)
{
    int i;
    printk(KERN_INFO "Passing command line arguments\n");
    printk(KERN_INFO "mystring is a string: %s\n", mystring);

    for (i = 0; i < (sizeof array1 / sizeof(int)); i++)
    {
        printk(KERN_INFO "array1[%d] = %d\n", i, array1[i]);
    }

    for (i = 0; i < (sizeof array2 / sizeof(int)); i++)
    {
        printk(KERN_INFO "array2[%d] = %d\n", i, array2[i]);
    }
    printk(KERN_INFO "array2 got %d arguments\n", count);
    return 0;
}
static void __exit modpass_exit(void)
{
    printk(KERN_INFO "Goodbye, passing command line arguments exiting…\n");
}

module_init(modpass_init);
module_exit(modpass_exit);
