#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/jiffies.h>

// preprocessor directive in C. It defines a macro named PROC_NAME and assigns it the value "jiffies"
#define PROC_NAME "jiffies"

// Function to handle reads from /proc/jiffies
static int jiffies_proc_show(struct seq_file *m, void *v){
    seq_printf(m, "%lu\n", jiffies); // Print the current value of jiffies
    return 0;
}

// Open function for the /proc file
static int jiffies_proc_open(struct inode *inode, struct file *file){
    return single_open(file, jiffies_proc_show, NULL);
}

static const struct proc_ops jiffies_proc_ops = {
    .proc_open = jiffies_proc_open;
    .proc_read = seq_read;
    .proc_lseek = seq_lseek,
    .proc_release = single_release,
};

static int __init jiffies_module_init(void)
{
    // Create the /proc/jiffies entry
    proc_create(PROC_NAME, 0, NULL, &jiffies_proc_ops);
    printk(KERN_INFO "/proc/%s created\n", PROC_NAME);
    return 0;
}


static void __exit jiffies_module_exit(void)
{
    remove_proc_entry(PROC_NAME, NULL);
    printk(KERN_INFO "/proc/%s removed\n", PROC_NAME);
}

module_init(jiffies_module_init);
module_exit(jiffies_module_exit);



MODULE_LICENCE("GPL");
MODULE_AUTHOR("OMPATEL");
MODULE_DESCRIPTION("GPL");
MODULE_VERSION("GPL");

