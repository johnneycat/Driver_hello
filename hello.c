//#include <Linux/init.h>

#include <linux/module.h>

#include <linux/kobject.h>

#include <linux/sysfs.h>

#include <linux/string.h>

static int hello_value;

//module_param(hello_value, int, 0555);

static ssize_t hello_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)

{

   return sprintf(buf, "%d\n", hello_value);

}

static ssize_t hello_store(struct kobject *kobj, struct kobj_attribute *attr, const char *buf, size_t count)

{

   sscanf(buf, "%du", &hello_value);

   return count;

}

static struct kobj_attribute hello_value_attribute = __ATTR(hello_value, 0664, hello_show, hello_store);

static struct kobject *helloworld_kobj;

static int __init helloworld_init(void)

{

   int retval;

   helloworld_kobj = kobject_create_and_add("helloworld", kernel_kobj);

   if (!helloworld_kobj)

             return -ENOMEM;

   retval = sysfs_create_file(helloworld_kobj, &hello_value_attribute.attr);

   if (retval)

      kobject_put(helloworld_kobj);

   return retval;

}

static void __exit helloworld_exit(void)

{

   kobject_put(helloworld_kobj);

}

module_init(helloworld_init);

module_exit(helloworld_exit);

MODULE_LICENSE("GPL");

//MODULE_AUTHER("doublenian.xie@gmail");