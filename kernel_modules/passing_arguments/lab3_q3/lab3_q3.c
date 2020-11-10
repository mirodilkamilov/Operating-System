#include <linux/init.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/kernel.h>

MODULE_LICENSE("Lab3 Q3");

static char *studentInfo[8] = {"Name", "ID", "Level", "Group No", "Address", "Ph. No", "Email address", "Grade"};
module_param_array(studentInfo, charp, NULL, 0); //not interested in count (NULL is passed)
static char *filename = "group_u1810031";
module_param(filename, charp, 0);

static int __init modpass_init(void)
{
    int i;

    printk(KERN_INFO "Lab#3 Q3\n");
    for (i = 0; i < 8; i++)
    {
        printk(KERN_INFO "studentInfo[%d] = %s\n", i, studentInfo[i]);
    }

    return 0;
}
static void __exit modpass_exit(void)
{
    printk(KERN_INFO "Goodbye, passing command line arguments exiting…\n");
}

module_init(modpass_init);
module_exit(modpass_exit);
