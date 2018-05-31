// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright (C) 2018 Ricardo Ribalda <ricardo.ribalda@gmail.com>
 *
 */

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/serdev.h>
#include <linux/usb.h>

#ifdef CONFIG_USB
static int find_ledctrl(struct usb_device *udev, void *p)
{
	struct device **pdev = p;

	if (le16_to_cpu(udev->descriptor.idVendor) != 0x0403)
		return 0;

	if (le16_to_cpu(udev->descriptor.idProduct) != 0x6001)
		return 0;

	*pdev = &udev->dev;

	return 1;
}

static struct serdev_controller *find_serdev(struct device *dev)
{
	int i = 0;
	struct serdev_controller *ctrl;
	struct device *aux;

	while ((ctrl = serdev_get_controller(i))) {
		aux = &ctrl->dev;

		while (aux) {
			if (aux == dev)
				return ctrl;

			aux = aux->parent;
		}

		serdev_put_controller(ctrl);
		i++;
	}

	return NULL;
}

#else

static struct serdev_controller *find_serdev(struct device *dev)
{
	return NULL;
}

#endif

static int __init test_init(void)
{
	struct serdev_controller *ctrl;
	struct device *dev = NULL;

	usb_for_each_dev(&dev, find_ledctrl);

	if (!dev) {
		printk(KERN_ERR "Usb device not found!\n");
		return 0;
	}

	ctrl = find_serdev(dev);
	if (!ctrl) {
		printk(KERN_ERR "Serdev not found!\n");
		return 0;
	}

	if (ctrl->serdev)
		serdev_device_remove(ctrl->serdev);

	serdev_controller_add_probed_device(ctrl, "qtec_ledctrl");

	serdev_put_controller(ctrl);

	return 0;
}

static void __exit test_exit(void)
{
}

module_init(test_init);
module_exit(test_exit);

MODULE_AUTHOR("Ricardo Ribalda");
MODULE_DESCRIPTION("Test platform driver for serdev");
MODULE_LICENSE("GPL");
