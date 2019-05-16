/*                                                     
 * $Id: hello.c,v 1.5 2004/10/26 03:32:21 corbet Exp $ 
 */                                                    
#include <linux/init.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/mm.h>
#include <linux/types.h>
#include <linux/kernel.h>
#include <linux/fs.h> 
#include <linux/cdev.h>
#include <asm/uaccess.h>


MODULE_LICENSE("Dual BSD/GPL");

dev_t dev;
int echo_major ;
int echo_minor = 0;
int echo_devs = 1;

struct cdev *cdp;





int echo_open (struct inode *inodep, struct file *filep){

	int ns_open;

	filep->private_data = cdp;

	ns_open = nonseekable_open(inodep , filep);


	printk( KERN_NOTICE " FILE OPENED\n");

	return 0 ;

}


int echo_release(struct inode *inodep , struct file *filep){


	printk(KERN_NOTICE " FILE WAS RELEASED\n");

	return 0 ;
}


ssize_t echo_read(struct file *filep , char __user *buff, size_t count, loff_t *offp ){

	unsigned long cp_t_user ;

	char *my_buf = kmalloc(count * sizeof(char ), GFP_KERNEL);

	cp_t_user = copy_to_user(buff , my_buf, count);

	if(cp_t_user > 0 ) return -1;


	printk(KERN_NOTICE "(READ) %s\n " , my_buf);

	//printk(KERN_NOTICE " READ !!!!!\n" );

	kfree(my_buf);

	return 0;

}


ssize_t echo_write(struct file *filep, const char __user *buff, size_t count, loff_t *offp){

unsigned long cp_f_user;

char *my_buf = kmalloc(count * sizeof(char), GFP_KERNEL);

cp_f_user = copy_from_user(my_buf , buff , count);

if(cp_f_user > 0 ) return -1;

my_buf[sizeof(my_buf)-1] = '\0';

printk(KERN_NOTICE  " (WRITE) %s \n ", my_buf);

kfree(my_buf);


return 0;

}




struct file_operations fops = {
	.owner =     THIS_MODULE,
	.open =	     echo_open,
	.release =   echo_release,
	.read = echo_read,
	.write = echo_write,
};




static int echo_init(void){

	int result, err;

	 dev = MKDEV(echo_major, 0) ;

	///alocação do major
	result = alloc_chrdev_region(&dev , 0 , echo_devs , "echo");
	echo_major = MAJOR(dev);

	///registar um dispositivo
	
	cdp = cdev_alloc();
	cdp->ops = &fops;
	cdp->owner = THIS_MODULE;

	err = cdev_add(cdp,dev,echo_devs);


	if( err < 0 ) printk(KERN_NOTICE " error adding device ");





	printk(KERN_ALERT " The major is  : %d\n", echo_major);

	return 0;
}

static void echo_exit(void){

	printk(KERN_ALERT "the major : %d was realeased \n", echo_major);

	unregister_chrdev_region(dev, echo_devs);

	cdev_del(cdp);

}







module_init(echo_init);
module_exit(echo_exit);
