// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright (C) 2018 Ricardo Ribalda <ricardo.ribalda@gmail.com>
 *
 */

#include <linux/kernel.h>
#include <linux/errno.h>
#include <linux/module.h>
#include <linux/serdev.h>
#include <linux/tty.h>
#include "serport.h"

static int ttydev_serdev_probe(struct serdev_device *serdev)
{
	struct serdev_controller *ctrl = serdev->ctrl;
	struct serport *serport;
	struct device *dev;

	if (!ctrl->is_ttyport)
		return -ENODEV;

	serport = serdev_controller_get_drvdata(ctrl);

	dev = tty_register_device_attr(serport->tty_drv, serport->tty_idx,
					&serdev->dev, NULL, NULL);

	return dev ? 0 : PTR_ERR(dev);
}

static void ttydev_serdev_remove(struct serdev_device *serdev)
{
	struct serdev_controller *ctrl = serdev->ctrl;
	struct serport *serport;

	serport = serdev_controller_get_drvdata(ctrl);
	tty_unregister_device(serport->tty_drv, serport->tty_idx);
}

static const struct serdev_device_id ttydev_serdev_id[] = {
	{ "ttydev", },
	{ "ttydev_serdev", },
	{}
};
MODULE_DEVICE_TABLE(serdev, ttydev_serdev_id);

static struct serdev_device_driver ttydev_serdev_driver = {
	.probe = ttydev_serdev_probe,
	.remove = ttydev_serdev_remove,
	.driver = {
		.name = "ttydev_serdev",
	},
	.id_table = ttydev_serdev_id,
};

module_serdev_device_driver(ttydev_serdev_driver);

MODULE_AUTHOR("Ricardo Ribalda <ricardo.ribalda@gmail.com>");
MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("Serdev to ttydev module");
