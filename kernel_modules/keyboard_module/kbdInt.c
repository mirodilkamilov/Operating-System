#include <linux/kernel.h> // FILE NAME : kbdAction.c
#include <linux/module.h>
#include <linux/interrupt.h>
#include <asm/io.h>

MODULE_LICENSE("GPL");

#define KBD_IRQ             1           /* IRQ number for keyboard (i8042) */
#define KBD_DATA_REG        0x60        /* I/O port for keyboard data register*/
#define KBD_STATUS          0x64        /* I/O port for keyboard status register */
#define KBD_SCANCODE_MASK   0x7f
#define KBD_STATUS_MASK     0x80

char key_name[] = " 1234567890-= qwertyuiop[] asdfghjkl;' zxcvbnm,./";

static irqreturn_t kbdInt_isr(int irq, void *dev_id)
{
    char scancode;
    char keypress;
    int status;
    
    status = inb(KBD_STATUS);
    pr_info("Your keyboard status is %d\n", status);
    scancode = inb(KBD_DATA_REG);
    keypress = key_name[scancode & KBD_SCANCODE_MASK];
    if (!(scancode & KBD_STATUS_MASK))
        pr_info("You have pressed the Key : %c , its Scan Code is %x and ASCII code - %d\n", keypress,
                scancode & KBD_SCANCODE_MASK, keypress);
    if (scancode & KBD_STATUS_MASK)
        pr_info("Now you have released the key %c and its Scan Code is %x\n", keypress, scancode);
    return IRQ_HANDLED;
}

static int __init kbdInt_init(void)
{
    return request_irq(KBD_IRQ, kbdInt_isr, IRQF_SHARED, "kbdInt", (void *)kbdInt_isr);
}
static void __exit kbdInt_exit(void)
{
    free_irq(KBD_IRQ, (void *)kbdInt_isr);
}

module_init(kbdInt_init);
module_exit(kbdInt_exit);